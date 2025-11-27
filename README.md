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

These structures can't contain pointers, since those will all be specified relative to the WASM memory, not the host memory.  Similarly, they can't contain function pointers (a core part of the CLAP API), so these are represented by `Pointer<>` and `Function<>` wrappers respectively. 

(This is why it's in C++, sorry C/Rust folks.  The `Pointer<>`/`Function<>` templates make this _so_ much nicer.  If it's possible to write something similar in other languages, I'm not the person to do it.)

### `Instance` interface

To actually set/get `Pointer<>`s, or call `Function<>`s, you need an `Instance`.  This is an abstract interface defined in `wclap/instance.hpp`.

The idea is to abstract "a WCLAP running in some unknown WASM engine", making it easier to write a host and swap the WASM engine out later.  WASI support is up to the `Instance`, and there may be some implementation-specific config there.

All host functions must be registered before calling `Instance::init()`, and will have different `Function<>` values when registered on different `Instance`s.

If a WCLAP spawns a new thread, the `Instance` should handle this internally, and then inform you about it by a callback on that new thread.  A thread spawned by one `Instance` will *not* be able to call methods on other `Instance`s.
