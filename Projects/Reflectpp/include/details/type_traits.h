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
#include <set>
#include <type_traits>
#include <vector>

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		using decay = std::remove_pointer_t<std::decay_t<T>>;

		template<typename>
		struct is_array : std::false_type {};
		template<typename T, size_t Size>
		struct is_array<std::array<T, Size>> : std::true_type {};

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

		template<typename>
		struct is_map : std::false_type {};
		template<typename T, typename Key>
		struct is_map<std::map<T, Key>> : std::true_type {};

		template<typename>
		struct is_multimap : std::false_type {};
		template<typename T, typename Key>
		struct is_multimap<std::multimap<T, Key>> : std::true_type {};

		template<typename>
		struct is_multiset : std::false_type {};
		template<typename Key>
		struct is_multiset<std::multiset<Key>> : std::true_type {};

		template<typename>
		struct is_set : std::false_type {};
		template<typename Key>
		struct is_set<std::set<Key>> : std::true_type {};

		template<typename>
		struct is_vector : std::false_type {};
		template<typename T>
		struct is_vector<std::vector<T>> : std::true_type {};

		template<typename T>
		struct is_associative_container : std::bool_constant<
			is_map<T>::value /*||
			is_multimap<T>::value ||
			is_multiset<T>::value ||
			is_set<T>::value*/>
		{};

		template<typename T>
		struct is_sequence_container : std::bool_constant<
			is_array<T>::value ||
			is_deque<T>::value ||
			is_forward_list<T>::value ||
			is_list<T>::value ||
			is_vector<T>::value>
		{};

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
	}
}
