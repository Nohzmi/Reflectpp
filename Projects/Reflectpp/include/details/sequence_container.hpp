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
#include <string>
#include <vector>

#include "details/macros.h"
#include "details/sequence_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(T) REFLECTPP_NOEXCEPT
		{
			return sequence_container_data<void>();
		}

		template<typename>
		struct is_sequence_container : std::false_type {};

		template<typename T, size_t Size>
		REFLECTPP_INLINE auto get_sequence_container_data(std::array<T, Size>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::array<T, Size>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_at = [](class_type* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T, size_t Size>
		struct is_sequence_container<std::array<T, Size>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::basic_string<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::basic_string<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_at = [](class_type* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::basic_string<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::deque<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::deque<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_at = [](class_type* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::deque<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::forward_list<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::forward_list<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				for (auto it = container->before_begin(); it != container->end(); ++it)
				{
					auto next = it;

					if (++next == pos)
						return container->erase_after(it);
				}

				return container->end();
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				for (auto it = container->before_begin(); it != container->end(); ++it)
				{
					auto next = it;

					if (++next == pos)
						return container->insert_after(it, value);
				}

				return container->end();
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::forward_list<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::list<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::list<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::list<T>> : std::true_type {};

		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::vector<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::vector<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_at = [](class_type* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}

		template<typename T>
		struct is_sequence_container<std::vector<T>> : std::true_type {};
	}
}
