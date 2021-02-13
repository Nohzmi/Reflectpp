// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		template<typename Container = void, typename Iterator = void, typename Key = void, typename Value = void>
		struct associative_container_data final
		{
			using class_type = Container;
			using iterator = Iterator;
			using key_type = Key;
			using value_type = Value;

			iterator (*m_begin)(class_type* container) { nullptr };
			void (*m_clear)(class_type* container) { nullptr };
			iterator (*m_end)(class_type* container) { nullptr };
			std::pair<iterator, iterator> (*m_equal_range)(class_type* container, const key_type& key) { nullptr };
			size_t (*m_erase)(class_type* container, const key_type& key) { nullptr };
			iterator (*m_find)(class_type* container, const key_type& key) { nullptr };
			std::pair<iterator, bool> (*m_insert)(class_type* container, const key_type& key, const value_type& value) { nullptr };
			size_t (*m_size)(class_type* container) { nullptr };
		};

		template<typename Container, typename Iterator, typename Key>
		struct associative_container_data<Container, Iterator, Key, void> final
		{
			using class_type = Container;
			using iterator = Iterator;
			using key_type = Key;

			iterator (*m_begin)(class_type* container) { nullptr };
			void (*m_clear)(class_type* container) { nullptr };
			iterator (*m_end)(class_type* container) { nullptr };
			std::pair<iterator, iterator> (*m_equal_range)(class_type* container, const key_type& key) { nullptr };
			size_t (*m_erase)(class_type* container, const key_type& key) { nullptr };
			iterator (*m_find)(class_type* container, const key_type& key) { nullptr };
			std::pair<iterator, bool> (*m_insert)(class_type* container, const key_type& key) { nullptr };
			size_t (*m_size)(class_type* container) { nullptr };
		};

		template<typename Container, typename Iterator>
		struct associative_container_data<Container, Iterator, void, void> final
		{
		};

		template<typename Container>
		struct associative_container_data<Container, void, void, void> final
		{
		};

		template<>
		struct associative_container_data<void, void, void, void> final
		{
		};
	}
}
