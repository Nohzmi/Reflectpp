// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_traits.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace reflectpp
{
	namespace details
	{
		template<typename>
		struct is_array : std::false_type {};
		template<typename T, size_t Size>
		struct is_array<std::array<T, Size>> : std::true_type {};

		///////
		template<typename>
		struct is_associative_container : std::false_type {};
		template<typename T, typename Key>
		struct is_associative_container<std::map<T, Key>> : std::true_type {};
		template<typename T, typename Key>
		struct is_associative_container<std::unordered_map<T, Key>> : std::true_type {};
		///////

		template<typename>
		struct is_deque : std::false_type {};
		template<typename T>
		struct is_deque<std::deque<T>> : std::true_type {};

		template<typename>
		struct is_forward_list : std::false_type {};
		template<typename T>
		struct is_forward_list<std::forward_list<T>> : std::true_type {};

		template<typename>
		struct is_list : std::false_type {};
		template<typename T>
		struct is_list<std::list<T>> : std::true_type {};

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

		template<typename>
		struct is_vector : std::false_type {};
		template<typename T>
		struct is_vector<std::vector<T>> : std::true_type {};

		template<typename T>
		using decay = std::remove_pointer_t<std::decay_t<T>>;
	}
}
