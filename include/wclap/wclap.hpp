#pragma once

#include <cstdint>
#include <type_traits>

#define WCLAP_CONSTEXPR constexpr
#define WCLAP_EXPORT
#define WCLAP_NODISCARD

#include "./_impl/wclap-defines.hpp"

namespace wclap32 {
	using Size = uint32_t;

	template<class T>
	struct Pointer {
		uint32_t wasmPointer;
		Pointer(uint32_t wasmPointer=0) : wasmPointer(wasmPointer) {}
		
		// Explicit because we *don't* want automatic conversion to integer, since that could silently convert between Pointer types
		explicit operator bool() const {
			return (bool)wasmPointer;
		}
		operator Pointer<const T>() const {
			return {wasmPointer};
		}
		
		template<class T2>
		Pointer<T2> cast() const {
			return {wasmPointer};
		}
		
		Pointer operator+(int32_t delta) {
			return {wasmPointer + delta*Size(sizeof(T))};
		}
		Pointer &operator+=(int32_t delta) {
			wasmPointer += delta*Size(sizeof(T));
			return *this;
		}
		
		// Use pointer[&T::member] -> pointer to field with appropriate offset
		template<class M, class T2>
		std::enable_if_t<std::is_same_v<std::remove_cv_t<T>, T2>, Pointer<M>> operator[](M T2::*ptr) {
			T tmp{};
			size_t offset = size_t(&(tmp.*ptr)) - size_t(&tmp);
			return {Size(wasmPointer + offset)};
		}
	};
	template<class Return, class... Args>
	struct Function {
		uint32_t wasmPointer;
	};

	#include "./_impl/wclap-generic.hpp"
};

namespace wclap64 {
	using Size = uint64_t;

	template<class T>
	struct Pointer {
		uint64_t wasmPointer;
		Pointer(uint64_t wasmPointer=0) : wasmPointer(wasmPointer) {}

		explicit operator bool() const {
			return (bool)wasmPointer;
		}

		operator Pointer<const T>() const {
			return {wasmPointer};
		}

		template<class T2>
		Pointer<T2> cast() const {
			return {wasmPointer};
		}

		Pointer operator+(int64_t delta) {
			return {wasmPointer + delta*Size(sizeof(T))};
		}
		Pointer &operator+=(int64_t delta) {
			wasmPointer += delta*Size(sizeof(T));
			return *this;
		}
		
		// Use pointer[&T::member] -> pointer to field with appropriate offset
		template<class M, class T2>
		std::enable_if_t<std::is_same_v<std::remove_cv_t<T>, T2>, Pointer<M>> operator[](M T2::*ptr) {
			T tmp{};
			size_t offset = size_t(&(tmp.*ptr)) - size_t(&tmp);
			return {Size(wasmPointer + offset)};
		}
	};
	template<class Return, class... Args>
	struct Function {
		uint64_t wasmPointer;
	};

	#include "./_impl/wclap-generic.hpp"
};
