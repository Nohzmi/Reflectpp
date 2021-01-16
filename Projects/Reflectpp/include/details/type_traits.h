// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_traits.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <list>
#include <type_traits>
#include <vector>

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		using decay = std::remove_pointer_t<std::decay_t<T>>;

		template <typename T>
		class is_registered
		{
		private:

			typedef char true_type[1];
			typedef char false_type[2];

			template <typename C>
			static true_type& test(decltype(&C::registered));

			template <typename C>
			static false_type& test(...);

		public:

			enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
		};

		template<typename>
		struct is_sequence_container : std::false_type {};

		template<typename T, typename A>
		struct is_sequence_container<std::vector<T, A>> : std::true_type {};

		template<typename T, typename A>
		struct is_sequence_container<std::list<T, A>> : std::true_type {};

		template<typename T>
		struct is_valid_param : std::bool_constant<
			!std::is_array_v<T> &&
			!std::is_null_pointer_v<T> &&
			!std::is_pointer_v<std::remove_pointer_t<std::decay_t<T>>> &&
			!std::is_void_v<T>>
		{};

		template<typename T>
		struct is_valid_type : std::bool_constant<
			!std::is_array_v<T> &&
			!std::is_const_v<T> &&
			!std::is_null_pointer_v<T> &&
			!std::is_pointer_v<T> &&
			!std::is_reference_v<T> &&
			!std::is_void_v<T> &&
			!std::is_volatile_v<T>>
		{};
	}
}
