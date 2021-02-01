// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

#include "details/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct type_data final
		{
			std::pair<void*, void*> (*m_associative_at)(void*, size_t) { nullptr };
			void (*m_associative_clear)(void*) { nullptr };
			std::pair<size_t, size_t> (*m_associative_equal_range)(void*, void*) { nullptr };
			size_t (*m_associative_erase)(void*, void*) { nullptr };
			size_t (*m_associative_find)(void*, void*) { nullptr };
			std::pair<size_t, bool> (*m_associative_insert)(void*, void*, void*) { nullptr };
			size_t (*m_associative_size)(void*) { nullptr };

			std::vector<type_data*> m_base_types;
			std::vector<type_data*> m_derived_types;
			factory_data* m_factory{ nullptr };
			size_t m_hierarchy_id{ 0 };
			bool m_is_associative_container{ false };
			bool m_is_sequence_container{ false };
			type_data* m_iterator_type{ nullptr };
			type_data* m_key_type{ nullptr };
			std::vector<property_data*> m_properties;

			void (*m_sequence_assign)(void*, size_t, void*) { nullptr };
			void* (*m_sequence_at)(void*, size_t) { nullptr };
			void (*m_sequence_clear)(void*) { nullptr };
			void (*m_sequence_erase)(void*, size_t) { nullptr };
			void (*m_sequence_insert)(void*, size_t, void*) { nullptr };
			void (*m_sequence_resize)(void*, size_t) { nullptr };
			size_t (*m_sequence_size)(void*) { nullptr };

			size_t m_size{ 0 };
			type_info_data* m_type_info{ nullptr };
			type_data* m_value_type{ nullptr };
			type_data* m_wrapped_type{ nullptr };
		};
	}
}
