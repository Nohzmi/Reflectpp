// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_traits.h
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
		using decay = std::remove_pointer_t<std::decay_t<T>>;

		template<typename T>
		struct is_arithmetic : std::integral_constant<bool,
			std::is_arithmetic_v<decay<T>>>
		{};

		template<typename T>
		struct is_constructible : std::integral_constant<bool,
			std::is_constructible_v<decay<T>>>
		{};

		template<typename T>
		struct is_copy_constructible : std::integral_constant<bool,
			std::is_copy_constructible_v<decay<T>>>
		{};

		template<typename T>
		struct is_destructible : std::integral_constant<bool,
			std::is_destructible_v<decay<T>>>
		{};

		template<typename T>
		struct is_null_pointer: std::integral_constant<bool,
			std::is_null_pointer_v<decay<T>>>
		{};

		template<typename T>
		struct is_pointer : std::integral_constant<bool,
			std::is_pointer_v<std::decay_t<T>>>
		{};

		template<typename T>
		struct is_pointer_of_pointer : std::integral_constant<bool,
			std::is_pointer_v<decay<T>>>
		{};

		template<typename T>
		struct is_reference : std::integral_constant<bool,
			std::is_reference_v<decay<T>>>
		{};

		template<typename T, typename U>
		struct is_same : std::integral_constant<bool,
			std::is_same_v<decay<T>, decay<U>>>
		{};

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

		template<typename T>
		struct is_valid_factory : std::bool_constant<
			std::is_same_v<T, decay<T>> &&
			!std::is_null_pointer_v<T> &&
			!std::is_void_v<T>>
		{};

		template <typename T>
		class use_macro
		{
		private:

			typedef char true_type[1];
			typedef char false_type[2];

			template <typename C>
			static true_type& test(decltype(&C::registered));

			template <typename C>
			static false_type& test(...);

		public:

			enum { value = sizeof(test<decay<T>>(0)) == sizeof(true_type) };
		};
	}
}
