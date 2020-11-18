// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utilities.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <type_traits>

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct is_valid : std::bool_constant<
			!std::is_array_v<T> &&
			!std::is_const_v<T> &&
			!std::is_null_pointer_v<T> &&
			!std::is_pointer_v<T> &&
			!std::is_reference_v<T> &&
			!std::is_void_v<T> &&
			!std::is_volatile_v<T>>
		{};

		template <typename T>
		class use_macro
		{
		private:

			typedef char true_type[1];
			typedef char false_type[2];

			template <typename C>
			static true_type& test(decltype(&C::type_id));

			template <typename C>
			static false_type& test(...);

		public:

			enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
		};

		template <class ...Args>
		void _assert(bool expr, const char* format, Args... args) noexcept;

		template<typename T>
		size_t type_id() noexcept;

		template<typename T>
		size_t type_id(T* object) noexcept;

		template<typename T>
		const char* type_name() noexcept;

		template<typename T>
		const char* type_name(T* object) noexcept;
	}
}

#include "details/inline/utilities.inl"
