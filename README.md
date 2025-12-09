# WCLAP C++ helpers

This repo contains WCLAP C++ headers (translated from the CLAP headers) as well as some helpers

## C++ API

This repo includes the C++ header `wclap/wclap.hpp` which defines WCLAP equivalents to all the CLAP types.  These have the (function-)pointers replaced, so (as long as the host architecture is little-endian) they can be copied bitwise from the corresponding CLAP types inside the WASM memory.

These structures can't contain pointers, since those will all be specified relative to the WASM memory, not the host memory.  Similarly, they can't contain function pointers (a core part of the CLAP API), so these are represented by `Pointer<>` and `Function<>` wrappers respectively. 

(This is why it's in C++, sorry C/Rust folks.  The `Pointer<>`/`Function<>` templates make this _so_ much nicer.  If it's possible to write something similar in other languages, I'm not the person to do it.)

## Helpers

### `Instance` interface

To actually set/get `Pointer<>`s, or call `Function<>`s, you need an `Instance`.  This defined in `wclap/instance.hpp`, and _mostly_ forwards directly to an underlying implementation, with the exception of:
* `instance.init()` -> `impl.init32()` or `impl.init64()` as appropriate
* `instance.get()`/`.set()` -> forward to `.getArray()`/`.setArray()` with length 1

The idea is to abstract "a WCLAP running in some unknown WASM engine", making it easier to write a host and swap the WASM engine out later.  WASI support is up to the `Instance`, and there may be some implementation-specific config there:

![wclap-cpp overview diagram](doc/wclap-cpp-outline.png)

Host functions can only be registered before calling `Instance::init()`.  This will produce different `Function<>` values when registered on different `Instance`s, so they must be stored per-instance.

If a WCLAP spawns a new thread, the `Instance` should handle this internally.  A thread spawned by one `Instance` _must_ not rely on being able to call methods on other `Instance`s.

### `IndexLookup<T>`

WCLAP hosts need to insert their own structures (e.g. `clap_host`) in the WCLAP memory, and the WCLAPs will point to those structures when calling host functions, but they shouldn't be trusted not to mess with them.

This is a simple helper which gives you indices to stick in the `void *` context fields of various CLAP host structures.  When a host function is called, you can then locate the corresponding plugin/etc. by index, with straightforward bounds checks for safety.

### `MemoryArenaPool` and `MemoryArena`

Each `MemoryArena` owns a chunk of the WCLAP's memory, and can use it to write function arguments or host structures.  These can be obtained (possibly created) from the WCLAP-wide pool, and returned to it when no longer needed.

Plugins should reserve an arena for their lifetime, both for persistently storing that plugin's host structs, and to lock and write arguments to when making realtime-thread function calls (since that arena is known to be available).
