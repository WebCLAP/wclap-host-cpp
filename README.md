# WCLAP

A WCLAP is a CLAP module compiled to WebAssembly (`wasm32` or `wasm64`).  It must:

* export `clap_entry` (an integer which is secretly `clap_plugin_entry *`)
* export `malloc()` or something like it (`void * malloc(size_t)`)
* import or export memory (which *may* be shared) - if it does both, hosts should ignore the export.

The `wasm32` architecture is the most widely supported, but hosts should still check the integer type of `clap_entry` and `malloc` to be sure.

If the WCLAP is a directory (or when fetched via URL, a `.tar.gz` which expands into a directory) then the actual binary should be `./module.wasm`.

The WCLAP may import WASI, and hosts should provide this where possible.  If the plugin is a directory, that entire directory should be available through the WASI filesystem (and pointed to in `clap_entry.init()`).

## WCLAP C++ API

This repo includes the C++ header `wclap/wclap.hpp` which defines WCLAP equivalents to all the CLAP types.  These have the (function-)pointers replaced, so (as long as the host architecture is little-endian) they can be copied bitwise from the corresponding CLAP types inside the WASM memory.

(Sorry, C/Rust folks - the `Pointer<>`/`Function<>` templates make this _so_ much nicer.)

### Recommended `Instance` API

This repo also includes `wclap/instance.hpp`, which is a _recommended_ API for abstracting different WASM engines.  Using this API should make it easier to write a host and swap the WASM engine out later.

Each `Instance` should correspond to a (thread for a) WASM VM running a WCLAP.  All CLAP host functions must be registered as soon as this is available, before `.init()` (or `.initThread()`) is called.  This ensures consistent function-pointer values across instances/threads.

### WASI helper

The files `wclap/wasi.hxx`defines functions suitable for implementing `wasi_snapshot_preview1`, but only the filesystem/env/args ones are defined. 

If this is backed by an actual filesystem, then the (non-exported) `wasi_set_directory()` function must be called at initialisation time, otherwise an in-memory one will be used.

Since this only provides a single filesystem, if you're hosting multiple WCLAPs then `wasi_create_plugin_dir()` should be called (and the result stored) to create/return a directory for the plugin to be placed in.  Directories outside of this cannot be listed with `fd_readdir()`, so plugins won't be able to read each others' data without sharing this.

This has not been thoroughly security-reviewed, but (after looking at security reports for other implementations), symlinks/links seemed to be the weak-point for sandboxing, so they are simply not supported.  They don't make as much sense on Windows anyway.
