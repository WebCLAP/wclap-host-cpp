#include "./wclap.hpp"

#include <functional>

namespace wclap {

// This defines/enforces the API, by just forwarding everything to the actual implementation
// Use `Instance<MyImpl &>` as a member field and return that.
template<class ActualImpl>
class Instance {
	ActualImpl impl;
	static int threadSpawnImpl(ActualImpl *impl, uint64_t startArg) {
		auto *self = *(Instance *)impl; // first field, has same address
		if (!self->threadSpawn) return -1; // not supported
		return self->threadSpawn(*self, startArg);
	}

public:
	template<class... Args>
	Instance(Args &&...args) : impl(std::forward<Args>(args)...) {
		impl.threadSpawn = threadSpawn;
	}
	
	bool is64() const {
		return impl.is64();
	}

	// Main thread - this should call _initialize() etc. but not clap_entry.init()
	wclap32::Pointer<wclap32::wclap_plugin_entry> init32() {
		return impl.init32();
	}
	wclap64::Pointer<wclap64::wclap_plugin_entry> init64() {
		return impl.init64();
	}

	// Thread-specific init - calls through to wasi_thread_start()
	void initThread(int threadId, void *startArg) {
		impl.initThread(threadId, startArg);
	}

	// This gets called by the instance when it wants to start a thread - assign this if you support threads, call initThread() from the new thread, and return thread ID [1, 2^29) on success, negative on failure
	int (*threadSpawn)(Instance *instance, uint64_t startArg) = nullptr;

	//---- wclap32 ----//

	template<class V>
	V get(wclap32::Pointer<V> ptr) {
		return impl.get(ptr);
	}
	template<class V>
	bool getArray(wclap32::Pointer<V> ptr, V *result, size_t count) {
		return impl.getArray(ptr, result, count);
	}

	template<class V>
	bool set(wclap32::Pointer<V> ptr, const V &value) {
		return impl.set(ptr, value);
	}
	template<class V>
	bool setArray(wclap32::Pointer<V> ptr, const V *value, size_t count) {
		return impl.setArray(ptr, value, count);
	}
	
	template<class V>
	uint32_t countUntil(wclap32::Pointer<V> ptr, V endValue, uint32_t maxCount){
		return impl.countUntil(ptr, endValue, maxCount);
	}

	template<class Return, class... Args>
	Return call(wclap32::Function<Return, Args...> fnPtr, Args... args) {
		return impl.call(fnPtr, args...);
	}

	wclap32::Pointer<void> malloc32(uint32_t size) {
		return impl.malloc32(size);
	}

	// You should actually implement registerHost64<Return, Args...>(fnPtr) instead of this
	template<auto fnPtr>
	auto registerHost32() {
		using FnType = decltype(std::function{fnPtr});
		return registerHost32Inner(fnPtr, FnType{});
	}

	//---- wclap64 ----//
	template<class V>
	V get(wclap64::Pointer<V> ptr) {
		return impl.get(ptr);
	}
	template<class V>
	bool getArray(wclap64::Pointer<V> ptr, V *result, size_t count) {
		return impl.getArray(ptr, result, count);
	}

	template<class V>
	bool set(wclap64::Pointer<V> ptr, const V &value) {
		return impl.set(ptr, value);
	}
	template<class V>
	bool setArray(wclap64::Pointer<V> ptr, const V *value, size_t count) {
		return impl.setArray(ptr, value, count);
	}
	
	template<class V>
	uint64_t countUntil(wclap64::Pointer<V> ptr, V endValue, uint64_t maxCount){
		return impl.countUntil(ptr, endValue, maxCount);
	}

	template<class Return, class... Args>
	Return call(wclap64::Function<Return, Args...> fnPtr, Args... args) {
		return impl.call(fnPtr, args...);
	}

	wclap64::Pointer<void> malloc64(uint32_t size) {
		return impl.malloc64(size);
	}

	// You should actually implement registerHost64<Return, Args...>(fnPtr) instead of this
	template<auto fnPtr>
	auto registerHost64() {
		using FnType = decltype(std::function{fnPtr});
		return registerHost64Inner(fnPtr, FnType{});
	}

private:
	// Template shenanigans, so you don't have to
	// The functions above use C++17's template-parameter deduction to fill out a std::function.  We then match on that here, to _expliclty_ template the `.registerHostN()` methods.
	template<typename Fn, typename Return, class ...Args>
	wclap32::Function<Return, Args...> registerHost32Inner(Fn fnPtr, const std::function<Return(Args...)> &) {
		impl.template registerHost32<Return, Args...>(fnPtr);
	}
	template<typename Fn, typename Return, class ...Args>
	wclap64::Function<Return, Args...> registerHost64Inner(Fn fnPtr, const std::function<Return(Args...)> &) {
		impl.template registerHost64<Return, Args...>(fnPtr);
	}
};

} // namespace
