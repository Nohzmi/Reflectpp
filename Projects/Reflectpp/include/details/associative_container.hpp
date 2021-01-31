// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "details/macros.h"
#include "details/associative_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_associative_container_data(T) REFLECTPP_NOEXCEPT
		{
			return associative_container_data();
		}

		template<typename>
		struct is_associative_container : std::false_type {};

		template<typename>
		struct has_value_type : std::false_type {};

		template<typename Key, typename T>
		REFLECTPP_INLINE auto get_associative_container_data(std::map<Key, T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::map<Key, T>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;
			using value_type = typename class_type::mapped_type;

			associative_container_data<class_type, iterator, key_type, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key, const value_type& value) -> std::pair<iterator, bool>
			{
				return container->insert(std::make_pair(key, value));
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key, typename T>
		struct is_associative_container<std::map<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::map<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		REFLECTPP_INLINE auto get_associative_container_data(std::multimap<Key, T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::multimap<Key, T>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;
			using value_type = typename class_type::mapped_type;

			associative_container_data<class_type, iterator, key_type, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key, const value_type& value) -> std::pair<iterator, bool>
			{
				return std::make_pair(container->insert(std::make_pair(key, value)), true);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key, typename T>
		struct is_associative_container<std::multimap<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::multimap<Key, T>> : std::true_type {};

		template<typename Key>
		REFLECTPP_INLINE auto get_associative_container_data(std::multiset<Key>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::multiset<Key>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;

			associative_container_data<class_type, iterator, key_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key) -> std::pair<iterator, bool>
			{
				return std::make_pair(container->insert(key), true);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key>
		struct is_associative_container<std::multiset<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::multiset<Key>> : std::false_type {};

		template<typename Key>
		REFLECTPP_INLINE auto get_associative_container_data(std::set<Key>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::set<Key>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;

			associative_container_data<class_type, iterator, key_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key) -> std::pair<iterator, bool>
			{
				return container->insert(key);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key>
		struct is_associative_container<std::set<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::set<Key>> : std::false_type {};

		template<typename Key, typename T>
		REFLECTPP_INLINE auto get_associative_container_data(std::unordered_map<Key, T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::unordered_map<Key, T>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;
			using value_type = typename class_type::mapped_type;

			associative_container_data<class_type, iterator, key_type, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key, const value_type& value) -> std::pair<iterator, bool>
			{
				return container->insert(std::make_pair(key, value));
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key, typename T>
		struct is_associative_container<std::unordered_map<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::unordered_map<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		REFLECTPP_INLINE auto get_associative_container_data(std::unordered_multimap<Key, T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::unordered_multimap<Key, T>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;
			using value_type = typename class_type::mapped_type;

			associative_container_data<class_type, iterator, key_type, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key, const value_type& value) -> std::pair<iterator, bool>
			{
				return std::make_pair(container->insert(std::make_pair(key, value)), true);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key, typename T>
		struct is_associative_container<std::unordered_multimap<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::unordered_multimap<Key, T>> : std::true_type {};

		template<typename Key>
		REFLECTPP_INLINE auto get_associative_container_data(std::unordered_multiset<Key>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::unordered_multiset<Key>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;

			associative_container_data<class_type, iterator, key_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key) -> std::pair<iterator, bool>
			{
				return std::make_pair(container->insert(key), true);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key>
		struct is_associative_container<std::unordered_multiset<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::unordered_multiset<Key>> : std::false_type {};

		template<typename Key>
		REFLECTPP_INLINE auto get_associative_container_data(std::unordered_set<Key>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::unordered_set<Key>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;

			associative_container_data<class_type, iterator, key_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key) -> std::pair<iterator, bool>
			{
				return container->insert(key);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename Key>
		struct is_associative_container<std::unordered_set<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::unordered_set<Key>> : std::false_type {};
	}
}
