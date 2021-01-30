// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <vector>

#include "details/macros.h"
#include "details/sequence_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE sequence_container_data<void> get_sequence_container_data(T) REFLECTPP_NOEXCEPT
		{
			return sequence_container_data<void>();
		}

		template<typename>
		struct is_sequence_container : std::false_type {};

		template<typename T, size_t Size>
		REFLECTPP_INLINE sequence_container_data<std::array<T, Size>> get_sequence_container_data(std::array<T, Size>) REFLECTPP_NOEXCEPT
		{
			using iterator = typename std::array<T, Size>::iterator;
			using value_type = typename std::array<T, Size>::value_type;

			sequence_container_data<std::array<T, Size>> data;

			data.m_at = [](std::array<T, Size>* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](std::array<T, Size>* container) -> iterator
			{
				return container->begin();
			};

			data.m_end = [](std::array<T, Size>* container) -> iterator
			{
				return container->end();
			};

			data.m_size = [](std::array<T, Size>* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T, size_t Size>
		struct is_sequence_container<std::array<T, Size>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE sequence_container_data<std::deque<T>> get_sequence_container_data(std::deque<T>) REFLECTPP_NOEXCEPT
		{
			using iterator = typename std::deque<T>::iterator;
			using value_type = typename std::deque<T>::value_type;

			sequence_container_data<std::deque<T>> data;

			data.m_at = [](std::deque<T>* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](std::deque<T>* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](std::deque<T>* container)
			{
				container->clear();
			};

			data.m_end = [](std::deque<T>* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](std::deque<T>* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](std::deque<T>* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](std::deque<T>* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](std::deque<T>* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::deque<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE sequence_container_data<std::forward_list<T>> get_sequence_container_data(std::forward_list<T>) REFLECTPP_NOEXCEPT
		{
			using iterator = typename std::forward_list<T>::iterator;
			using value_type = typename std::forward_list<T>::value_type;

			sequence_container_data<std::forward_list<T>> data;

			data.m_begin = [](std::forward_list<T>* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](std::forward_list<T>* container)
			{
				container->clear();
			};

			data.m_end = [](std::forward_list<T>* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](std::forward_list<T>* container, iterator pos) -> iterator
			{
				return container->erase_after(pos);
			};

			data.m_insert = [](std::forward_list<T>* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert_after(pos, value);
			};

			data.m_resize = [](std::forward_list<T>* container, size_t count)
			{
				container->resize(count);
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::forward_list<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE sequence_container_data<std::list<T>> get_sequence_container_data(std::list<T>) REFLECTPP_NOEXCEPT
		{
			using iterator = typename std::list<T>::iterator;
			using value_type = typename std::list<T>::value_type;

			sequence_container_data<std::list<T>> data;

			data.m_begin = [](std::list<T>* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](std::list<T>* container)
			{
				container->clear();
			};

			data.m_end = [](std::list<T>* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](std::list<T>* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](std::list<T>* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](std::list<T>* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](std::list<T>* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::list<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE sequence_container_data<std::vector<T>> get_sequence_container_data(std::vector<T>) REFLECTPP_NOEXCEPT
		{
			using iterator = typename std::vector<T>::iterator;
			using value_type = typename std::vector<T>::value_type;
	
			sequence_container_data<std::vector<T>> data;

			data.m_at = [](std::vector<T>* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](std::vector<T>* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](std::vector<T>* container)
			{
				container->clear();
			};

			data.m_end = [](std::vector<T>* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](std::vector<T>* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](std::vector<T>* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](std::vector<T>* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](std::vector<T>* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::vector<T>> : std::true_type {};
	}
}
