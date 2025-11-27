#include <shared_mutex>
#include <type_traits>

namespace wclap {

template<class Instance, bool is64>
struct MemoryArenaManager;

template<class Instance, bool is64>
struct MemoryArena {
	using Pointer = std::conditional_t<is64, uint64_t, uint32_t>;
	static constexpr Pointer size = 16384;

	Pointer start, end;
	
	MemoryArena(Instance *instance) : instance(instance) {
		if (is64) {
			start = Pointer(instance->malloc64(uint64_t(size)));
			end = start + size;
		} else {
			start = Pointer(instance->malloc32(uint32_t(size)));
			end = start + size;
		}
	}
private:
	Instance *instance;
};

template<class Instance, bool is64>
struct MemoryArenaManager {
	MemoryArenaManager(Instance *instance) : instance(instance) {
	}
	
	MemoryArena<Instance, is64> getArena() {
		return {instance};
	}
	
private:
	Instance *instance;
};

} // namespace
