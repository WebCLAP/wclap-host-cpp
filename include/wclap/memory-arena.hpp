#include "./wclap.hpp"

#include <shared_mutex>
#include <type_traits>
#include <cstring>

namespace wclap {

template<class Instance, bool is64>
struct MemoryArenaManager;

template<class Instance, bool is64>
struct MemoryArena {
	using Size = std::conditional_t<is64, uint64_t, uint32_t>;
	template<class V>
	using Pointer = std::conditional_t<is64, wclap64::Pointer<V>, wclap32::Pointer<V>>;

	bool ok = false;
	
	MemoryArena(Instance *instance, Size size=16384) : instance(instance) {
		if (is64) {
			start = Size(instance->malloc64(uint64_t(size)));
			end = start + size;
		} else {
			start = Size(instance->malloc32(uint32_t(size)));
			end = start + size;
		}
		cleanStart = start;
		if (start) ok = true;
	}

	void clear() {
		start = cleanStart;
	}

	struct Scoped {
		~Scoped() {
			arena.start = restoreStart;
		}
		Scoped(const Scoped &other) = delete;
		
		void commit() {
			restoreStart = arena.start;
		}

		Pointer<const char> writeString(const char *str) {
			Pointer<char> remoteStr{arena.start};

			auto length = std::strlen(str);
			arena.start += length + 1;
			arena.instance->setArray(remoteStr, str, length + 1/* includes null-terminator*/);

			return remoteStr;
		}
	private:
		friend struct MemoryArena;
		MemoryArena &arena;
		Size restoreStart;

		Scoped(MemoryArena &arena) : arena(arena), restoreStart(arena.start) {}
	};
	
	Scoped scoped() {
		return Scoped(*this);
	}
	
private:
	Size start, end;
	Size cleanStart;
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
