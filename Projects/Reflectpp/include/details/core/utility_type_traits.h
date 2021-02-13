// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utility_type_traits.h
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace reflectpp
{
	namespace details
	{
		template <typename T>
		class has_operator_equal
		{
		private:

			typedef char true_type[1];
			typedef char false_type[2];

			template <typename C>
			static true_type& test(decltype(&C::operator==));

			template <typename C>
			static false_type& test(...);

		public:

			enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
		};

		template<typename>
		struct is_std_container : std::false_type {};
		template<typename T, size_t Size>
		struct is_std_container<std::array<T, Size>> : std::true_type {};
		template<typename T>
		struct is_std_container<std::deque<T>> : std::true_type {};
		template<typename T>
		struct is_std_container<std::forward_list<T>> : std::true_type {};
		template<typename T>
		struct is_std_container<std::list<T>> : std::true_type {};
		template<typename Key, typename T>
		struct is_std_container<std::map<Key, T>> : std::true_type {};
		template<typename Key, typename T>
		struct is_std_container<std::multimap<Key, T>> : std::true_type {};
		template<typename Key>
		struct is_std_container<std::multiset<Key>> : std::true_type {};
		template<typename Key>
		struct is_std_container<std::set<Key>> : std::true_type {};
		template<typename Key, typename T>
		struct is_std_container<std::unordered_map<Key, T>> : std::true_type {};
		template<typename Key, typename T>
		struct is_std_container<std::unordered_multimap<Key, T>> : std::true_type {};
		template<typename Key>
		struct is_std_container<std::unordered_multiset<Key>> : std::true_type {};
		template<typename Key>
		struct is_std_container<std::unordered_set<Key>> : std::true_type {};
		template<typename T>
		struct is_std_container<std::vector<T>> : std::true_type {};
	}
}
