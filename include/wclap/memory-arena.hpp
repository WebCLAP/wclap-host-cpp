#pragma once

#include "./wclap.hpp"

#include <mutex>
#include <shared_mutex>
#include <type_traits>
#include <cstring>
#include <vector>

namespace wclap {

template<class Instance, bool is64>
struct MemoryArenaPool;

template<class Instance, bool is64>
struct MemoryArena {
	using Size = std::conditional_t<is64, uint64_t, uint32_t>;
	template<class V>
	using Pointer = std::conditional_t<is64, wclap64::Pointer<V>, wclap32::Pointer<V>>;
	using ArenaPool = MemoryArenaPool<Instance, is64>;

	ArenaPool &pool;
	bool ok = false;

	MemoryArena(ArenaPool &pool, Instance *instance, Size size=16384) : pool(pool), instance(instance) {
		if constexpr (is64) {
			start = instance->malloc64(size).wasmPointer;
		} else {
			start = instance->malloc32(size).wasmPointer;
		}
		end = start + size;
		cleanStart = start;
		if (start) ok = true;
	}

	void clear() {
		start = cleanStart;
	}

	// Restores the arena pointer to a previous value when it drops out of scope, or (if `borrowedArena` set) return the Arena itself to the pool.
	struct Scoped {
		~Scoped() {
			arena.start = restoreStart;
			if (borrowedArena) {
				borrowedArena->pool.returnToPool(borrowedArena);
			}
		}
		Scoped(const Scoped &other) = delete;

		void reset() {
			arena.start = restoreStart;
		}

		std::unique_ptr<MemoryArena> commit() {
			restoreStart = arena.start;
			std::unique_ptr<MemoryArena> ptr = std::move(borrowedArena);
			return ptr;
		}

		Pointer<void> reserve(size_t length, size_t align) {
			while (arena.start%align) ++arena.start;
			Pointer<void> ptr{arena.start};
			arena.start += length;
			if (arena.start > arena.end) return {0}; // TODO: grow arena
			return ptr;
		}

		template<class T>
		Pointer<T> array(size_t length) {
			return reserve(length*sizeof(T), alignof(T)).template cast<T>();
		}

		Pointer<const char> writeString(const char *str) {
			auto length = std::strlen(str) + 1; // includes null-terminator
			auto remoteStr = array<char>(length);
			arena.instance->setArray(remoteStr, str, length);
			return remoteStr;
		}
		template<class V>
		Pointer<V> copyAcross(const V &v) {
			auto ptr = reserve(sizeof(V), alignof(V)).template cast<V>();
			arena.instance->set(ptr, v);
			return ptr;
		}
				
	private:
		friend struct MemoryArena;
		friend struct MemoryArenaPool<Instance, is64>;
		MemoryArena &arena;
		Size restoreStart;
		std::unique_ptr<MemoryArena> borrowedArena;
		std::scoped_lock<std::recursive_mutex> arenaLock;
		
		Scoped(MemoryArena &arena, std::unique_ptr<MemoryArena> borrowedArena) : arena(arena), borrowedArena(std::move(borrowedArena)), restoreStart(arena.start), arenaLock(arena.scopeMutex) {}
	};
	
	Scoped scoped() {
		return Scoped(*this, nullptr);
	}
	
private:
	std::recursive_mutex scopeMutex;
	Size start = 0, end = 0;
	Size cleanStart = 0;
	Instance *instance = nullptr;
};

template<class Instance, bool is64>
struct MemoryArenaPool {
	using Arena = MemoryArena<Instance, is64>;
	using ArenaPtr = std::unique_ptr<Arena>;

	MemoryArenaPool(Instance *instance) : instance(instance) {}
	
	auto readLock() {
		return std::shared_lock<std::shared_mutex>{mutex};
	}
	auto writeLock() {
		return std::unique_lock<std::shared_mutex>{mutex};
	}
	
	ArenaPtr getOrCreate() {
		{
			auto lock = readLock();
			if (arenaPool.empty()) {
				return ArenaPtr{new Arena(*this, instance)};
			}
		}
		auto lock = writeLock();
		if (arenaPool.empty()) { // In case it was popped off while we weren't locked
			return ArenaPtr{new Arena(*this, instance)};
		}
		auto result = std::move(arenaPool.back());
		arenaPool.pop_back();
		return result;
	}
	void returnToPool(ArenaPtr &ptr) {
		ptr->clear();
		auto lock = writeLock();
		arenaPool.emplace_back(std::move(ptr));
	}
	typename Arena::Scoped scoped() {
		auto arena = getOrCreate();
		return {*arena, std::move(arena)};
	}
private:
	Instance *instance;

	std::shared_mutex mutex;
	std::vector<ArenaPtr> arenaPool;
};

} // namespace
