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
		template<typename T, typename Key, typename Value = void>
		struct associative_container_data final
		{
			using iterator = typename T::iterator;
			using key_type = Key;
			using value_type = Value;

			iterator (*m_begin)(T* container) { nullptr };
			void (*m_clear)(T* container) { nullptr };
			iterator (*m_end)(T* container) { nullptr };
			std::pair<iterator, iterator> (*m_equal_range)(T* container, const key_type& key) { nullptr };
			size_t(*m_erase)(T* container, const key_type& key) { nullptr };
			iterator (*m_find)(T* container, const key_type& key) { nullptr };
			const bool m_has_value_type{ true };
			std::pair<iterator, bool> (*m_insert)(T* container, const key_type& key, const value_type& value) { nullptr };
			size_t (*m_size)(T* container) { nullptr };
		};

		template<typename T, typename Key>
		struct associative_container_data<T, Key, void> final
		{
			using iterator = typename T::iterator;
			using key_type = Key;

			iterator (*m_begin)(T* container) { nullptr };
			void (*m_clear)(T* container) { nullptr };
			iterator (*m_end)(T* container) { nullptr };
			std::pair<iterator, iterator> (*m_equal_range)(T* container, const key_type& key) { nullptr };
			size_t (*m_erase)(T* container, const key_type& key) { nullptr };
			const bool m_has_value_type{ false };
			iterator (*m_find)(T* container, const key_type& key) { nullptr };
			std::pair<iterator, bool> (*m_insert)(T* container, const key_type& key) { nullptr };
			size_t (*m_size)(T* container) { nullptr };
		};

		template<>
		struct associative_container_data<void, void, void> final
		{
		};
	}
}
