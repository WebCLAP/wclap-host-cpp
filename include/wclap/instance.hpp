#include "./wclap.hpp"

#include <functional>
#include <type_traits>

namespace wclap {

// This defines/enforces the API, by just forwarding everything to the actual implementation
// Use `Instance<MyImpl &>` as a member field and return that.
template<class ActualImpl>
class Instance {
	ActualImpl impl;
	static int threadSpawnImpl(void *impl, uint64_t startArg) {
		auto *self = (Instance *)impl;
		if (!self->threadSpawn) return -1; // not supported
		return self->threadSpawn(self->threadSpawnContext, startArg);
	}

public:
	template<class... Args>
	Instance(Args &&...args) : impl(std::forward<Args>(args)...) {
		impl.threadSpawnContext = this;
		impl.threadSpawn = threadSpawnImpl;
	}
	
	// Path inside its own virtual filesystem
	const char * path() const {
		return impl.path();
	}
	
	bool is64() const {
		return impl.is64();
	}

	// Entry-points - not populated until the module is initialised
	wclap32::Pointer<const wclap32::wclap_plugin_entry> entry32{0};
	wclap64::Pointer<const wclap64::wclap_plugin_entry> entry64{0};
	
	// Main thread - this should call _initialize() etc. but not clap_entry.init()
	// You should implement `init32()`/`init64()` which return the corresponding entry points
	void init() {
		if (is64()) {
			entry64 = impl.init64();
		} else {
			entry32 = impl.init32();
		}
	}

	// run a thread until stopped - calls through to wasi_thread_start() in the WCLAP
	void runThread(int threadId, void *startArg) {
		impl.runThread(threadId, startArg);
	}

	void *threadSpawnContext = nullptr;
	// This gets called by the instance when the WCLAP requests to start a thread - assign this if you support threads, returning thread ID [1, 2^29) on success, negative on failure, and then call runThread() from the new thread
	int (*threadSpawn)(void *threadContext, uint64_t startArg) = nullptr;

	//---- wclap32 ----//

	wclap32::Pointer<void> malloc32(uint32_t size) {
		return impl.malloc32(size);
	}

	// Helper, calls as length-1 array
	template<class V>
	std::remove_cv_t<V> get(wclap32::Pointer<V> ptr, size_t index=0) {
		std::remove_cv_t<V> value{};
		wclap32::Pointer<V> indexPtr{ptr.wasmPointer + uint32_t(sizeof(V)*index)};
		getArray(indexPtr, &value, 1);
		return value;
	}
	template<class V>
	bool set(wclap32::Pointer<V> ptr, std::remove_cv_t<V> value, size_t index=0) {
		wclap32::Pointer<V> indexPtr{ptr.wasmPointer + uint32_t(sizeof(V)*index)};
		return setArray(ptr, value, 1);
	}

	template<class V>
	bool getArray(wclap32::Pointer<V> ptr, std::remove_cv_t<V> *result, size_t count) {
		return impl.getArray(ptr, result, count);
	}
	template<class V>
	bool setArray(wclap32::Pointer<V> ptr, const V *value, size_t count) {
		return impl.setArray(ptr, value, count);
	}
	
	template<class V, class VE>
	uint32_t countUntil(wclap32::Pointer<V> ptr, const VE &endValue, uint32_t maxCount=-1) {
		return impl.template countUntil<V>(ptr, V(endValue), maxCount);
	}

	template<class Return, class... Args, class... CArgs>
	Return call(wclap32::Function<Return, Args...> fnPtr, CArgs... args) {
		// Strongly matches on the function args, but then implicitly converts here
		return impl.template call<Return, Args...>(fnPtr, args...);
	}

	template<class Return, class ...Args>
	wclap32::Function<Return, Args...> registerHost32(Return (*fn)(Args...)) {
		return impl.template registerHost32<Return, Args...>(fn);
	}

	//---- wclap64 ----//

	wclap64::Pointer<void> malloc64(uint64_t size) {
		return impl.malloc64(size);
	}

	// Helper, calls as length-1 array
	template<class V>
	std::remove_cv_t<V> get(wclap64::Pointer<V> ptr, size_t index=0) {
		std::remove_cv_t<V> value{};
		wclap64::Pointer<V> indexPtr{ptr.wasmPointer + uint64_t(sizeof(V)*index)};
		getArray(indexPtr, &value, 1);
		return value;
	}
	template<class V>
	bool set(wclap64::Pointer<V> ptr, std::remove_cv_t<V> value, size_t index=0) {
		wclap64::Pointer<V> indexPtr{ptr.wasmPointer + uint64_t(sizeof(V)*index)};
		return setArray(ptr, value, 1);
	}

	template<class V>
	bool getArray(wclap64::Pointer<V> ptr, std::remove_cv_t<V> *result, size_t count) {
		return impl.getArray(ptr, result, count);
	}
	template<class V>
	bool setArray(wclap64::Pointer<V> ptr, const V *value, size_t count) {
		return impl.setArray(ptr, value, count);
	}
	
	template<class V, class VE>
	uint64_t countUntil(wclap64::Pointer<V> ptr, VE endValue, uint64_t maxCount=-1){
		return impl.template countUntil<V>(ptr, V(endValue), maxCount);
	}

	template<class Return, class... Args, class... CArgs>
	Return call(wclap64::Function<Return, Args...> fnPtr, CArgs... args) {
		return impl.template call<Return, Args...>(fnPtr, args...);
	}

	template<class Return, class ...Args>
	wclap64::Function<Return, Args...> registerHost64(Return (*fn)(Args...)) {
		return impl.template registerHost64<Return, Args...>(fn);
	}
};

} // namespace
