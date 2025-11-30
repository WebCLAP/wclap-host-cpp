/* This keeps a mapping from 32-bit indices to object pointers.  It will always return either a valid object pointer, or `nullptr`.

This is useful for sticking in `host.host_data` or similar context fields, because we don't have to trust the values coming back from the WCLAP.

Currently this uses a `shared_mutex`, which is non-blocking *unless* items are being added/removed from the list.  It should be possible to implement in a completely lock-free way for `.get()`, but this will do for now.
*/

#include <vector>
#include <shared_mutex>

namespace wclap {

template<class T>
struct IndexLookup {
	// Transfers ownership in
	uint32_t retain(T *t) {
		std::unique_lock guard{mutex};
		size_t index = list.size();
		for (size_t i = 0; i < list.size(); ++i) {
			if (!list[i]) { // entries get nulled, not removed, so we search for an empty one first
				index = i;
				break;
			}
		}
		if (index >= list.size()) list.emplace_back(nullptr);
		list[index] = std::unique_ptr<T>{t};
		return index;
	}
	T * get(uint32_t index) {
		std::shared_lock guard{mutex};
		if (index >= list.size()) return nullptr;
		return list[index].get(); // could still be null if removed
	}
	void release(uint32_t index) {
		std::unique_lock guard{mutex};
		if (index < list.size()) list[index] = nullptr;
	}
private:
	std::shared_mutex mutex;
	std::vector<std::unique_ptr<T>> list;
};

} // namespace
