// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_traits.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <map>
#include <set>
#include <type_traits>

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		using decay = std::remove_pointer_t<std::decay_t<T>>;

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
