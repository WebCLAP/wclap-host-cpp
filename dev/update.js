"use strict"
const fs = require('fs'), resolvePath = require('path').resolve;
const clapPathPrefix = __dirname + "/clap/include/clap";

try {
	fs.accessSync(clapPathPrefix);
} catch (e) {
	require('child_process').execSync(`git clone https://github.com/free-audio/clap.git ${__dirname}/clap`);
}

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
let cppDefines = ``;

function addCode(code, toConstants) {
	code = code.replace(/([^a-zA-Z0-9_])clap_/g, "$1wclap_");
	code = code.replace(/([^a-zA-Z0-9_])CLAP_/g, "$1WCLAP_");
	// remove `_t` suffix from WCLAP types
	code = code.replace(/((\s+|\(|\*)wclap_[a-zA-Z0-9_]+)_t([^a-zA-Z0-9_])/g, "$1$3");
	
	// Replace all value pointers with a `Pointer<>` template
	let prevCode;
	do {
		prevCode = code;
		code = code.replace(/(\w[a-zA-Z0-9_\s<>]+?)(\s*)\*/, (match, type, whitespace) => {
			if (/^typedef\s/.test(type)) {
				type = type.replace(/^typedef\s/, '');
				return `typedef Pointer<${type}>${whitespace}`;
			}
			return `Pointer<${type}>${whitespace}`;
		});
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
	
	if (toConstants) {
		cppDefines += code + "\n";
	} else {
		cppHeader += code + "\n";
	}
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
	
	if (/^\/private\//.test(path)) return;

	let code = fs.readFileSync(`${clapPathPrefix}${path}`, 'utf8');
	// remove comments
	code = code.replaceAll(/\s*\/\/[^\n]*/g, '');
	code = code.replaceAll(/\/\*(.|\r|\n)*\*\//g, '');
	// tidying
	code = code.replaceAll(/(^|\n)\s*#pragma once/g, '');
	code = code.replaceAll(/#ifdef __cplusplus(.|\n)*?#endif/g, "");
	// This makes it easier to match on function pointers
	code = code.replaceAll(/\s*CLAP_ABI\s+/g, '');
	
	code = code.replaceAll(/#include\s+("[^"]+")/g, (match, includePath) => {
		includePath = JSON.parse(includePath);
		if (/^private\//.test(includePath)) return "";
		addFile(path.replace(/[^\/]*$/, '') + includePath);
		return "";
	});

	cppHeader += `//---------- ${path.substr(1)}\n`;
	cppDefines += `//---------- ${path.substr(1)}\n`;

	// catch all named defines
	code = code.replaceAll(/#define\s+CLAP_([^;\n\\]|\\(.|\r|\n))+/g, match => {
		addCode(match, true);
		return "";
	});

	addCode(code);
	return;
}

fs.writeFileSync("../include/wclap/_impl/wclap-generic.hpp", cppHeader);
fs.writeFileSync("../include/wclap/_impl/wclap-defines.hpp", cppDefines);

