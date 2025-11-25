"use strict"
const fs = require('fs'), resolvePath = require('path').resolve;
const clapPathPrefix = __dirname + "/clap/include/clap";

let knownNotNames = {};
'const,char,uint8_t,'.split(',').forEach(x => knownNotNames[x] = true);
let includedFiles = {};
let numericConstants = {};

let cppHeader = `
/* Generated code - do not edit by hand.

This includes all the CLAP API typedefs and structs, but:
	* renamed clap_ -> wclap_
	* T * replaced by Pointer<T>
	* function pointers replaced by Function<Return, Args...>

You should be able to include this inside another namespace, as long as Function<> and Pointer<> are defined.  These must be simple wrappers around integers, and have the same size as pointers inside the WASM module.
*/

`;

function addCode(code) {
	for (let key in numericConstants) code = code.replaceAll(key, numericConstants[key]);
	code = code.replace(/(\s+|\(|\*)clap_/g, "$1wclap_");
	// remove `_t` suffix from WCLAP types
	code = code.replace(/((\s+|\(|\*)wclap_[a-zA-Z0-9_]+)_t([^a-zA-Z0-9_])/g, "$1$3");
	
	// Replace all value pointers with a `Pointer<>` template
	let prevCode;
	do {
		prevCode = code;
		code = code.replace(/(\w[a-zA-Z0-9_\s<>]+?)(\s*)\*/, "Pointer<$1>$2");
	} while (prevCode != code);
	
	// Replace all function pointers
	code = code.replace(/(\w[a-zA-Z0-9_\s<>]+)\(\s*\*\s*([a-zA-Z0-9_]+)\s*\)\s*\(([^)]*)\)\s*;/g, (match, returnType, name, args) => {
		// remove name from pointer arguments
		args = args.replaceAll(/\s*([a-zA-Z0-9_]+)\s*($|,)/g, (match, token, next) => {
			if (knownNotNames[token]) return token + next;
			return next;
		});
		args = args.replace(/\n/g, ' ');
		return `Function<${returnType}${args.length?',':''}${args}> ${name};`;
	});
	// Just tidying, for personal satisfaction
	code = code.replace(/([^\s])[ \r]+/g, "$1 ");
	code = code.replace(/\s+,/g, ",");
	code = code.replace(/,([^\s])/g, ", $1");
	code = code.replace(/\n\s*\n/g, "\n");
	
	cppHeader += code + "\n";
}

addDir("");
addDir("/factory");
addDir("/factory/draft");
addDir("/ext");
addDir("/ext/draft");

function addDir(path) {
	let files = fs.readdirSync(clapPathPrefix + path);
	files.forEach(file => {
		if (/\.h$/.test(file)) addFile(`${path}/${file}`);
	});
}

function addFile(path) {
	path = resolvePath(path);
	if (includedFiles[path]) return;
	includedFiles[path] = true;

	let code = fs.readFileSync(`${clapPathPrefix}${path}`, 'utf8');
	code = code.replaceAll(/\s*\/\/[^\n]*/g, ''); // remove comments
	code = code.replaceAll(/\s*CLAP_ABI\s+/g, '');
	
	code.replaceAll(/#include\s+("[^"]+")/g, (match, includePath) => {
		includePath = JSON.parse(includePath);
		if (/^private\//.test(includePath)) return;
		addFile(path.replace(/[^\/]*$/, '') + includePath);
	});

	// catch numeric constants
	code.replaceAll(/#define\s+([a-zA-Z_][a-zA-Z0-9_]*)\s+([0-9]+)/g, (match, name, value) => {
		numericConstants[name] = parseInt(value);
	});
	// catch enum constants
	code.replaceAll(/enum\s+\{([^\}]+)\}/g, (match, body) => {
		body.replaceAll(/([a-zA-Z_][a-zA-Z0-9_]*)\s+=([^\,]+)/g, (match, name, value) => {
			value = value.trim();
			try {
				// There are a few different syntaxes here, and JS is close enough to C for this to work
				value = eval(value);
			} catch (e) {
				throw Error(`couldn't understand enum constant: ${name} = ${value}`);
			}
			numericConstants[name] = value;
		});
	});
	
	// catch simple typedefs
	code.replaceAll(/typedef\s+(([^\{\};]+)(\s+|\*)([a-zA-Z_][a-zA-Z0-9_]*);)/g, (match, body) => {
		cppHeader += "typedef ";
		addCode(body);
	});
	
	// Catch typedef'd structs, which are the main API type
	let parts = code.split('\ntypedef struct ');
	parts.slice(1).forEach((code, sliceIndex) => {
		let name = code.split(/\s/, 1)[0];
		// Extract struct body - it will end with the `_t` name.
		let body = code.substr(name.length).split(name + '_t')[0].trim();

		addCode(`struct ${name} ${body.trim()};`);
	});
}

fs.writeFileSync("../include/wclap/_impl/wclap-generic.hpp", cppHeader);
