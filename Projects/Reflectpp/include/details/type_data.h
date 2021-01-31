// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

#include "details/forward.h"
#include "details/typedef.h"

namespace reflectpp
{
	namespace details
	{
		struct type_data final
		{
			AssociativeAt m_associative_at{ nullptr };
			AssociativeClear m_associative_clear{ nullptr };
			AssociativeEqualRange m_associative_equal_range{ nullptr };
			AssociativeErase m_associative_erase{ nullptr };
			AssociativeFind m_associative_find{ nullptr };
			AssociativeInsert m_associative_insert{ nullptr };
			AssociativeInsertKey m_associative_insert_key{ nullptr };
			AssociativeInsertKeyValue m_associative_insert_key_value{ nullptr };
			AssociativeSize m_associative_size{ nullptr };
			std::vector<type_data*> m_base_types;
			std::vector<type_data*> m_derived_types;
			factory_data* m_factory{ nullptr };
			size_t m_hierarchy_id{ 0 };
			bool m_is_associative_container{ false };
			bool m_is_sequence_container{ false };
			type_data* m_iterator_type{ nullptr };
			type_data* m_key_type{ nullptr };
			std::vector<property_data*> m_properties;
			SequenceAssign m_sequence_assign{ nullptr };
			SequenceAt m_sequence_at{ nullptr };
			SequenceClear m_sequence_clear{ nullptr };
			SequenceErase m_sequence_erase{ nullptr };
			SequenceInsert m_sequence_insert{ nullptr };
			SequenceResize m_sequence_resize{ nullptr };
			SequenceSize m_sequence_size{ nullptr };
			size_t m_size{ 0 };
			type_info_data* m_type_info{ nullptr };
			type_data* m_value_type{ nullptr };
			type_data* m_wrapped_type{ nullptr };
		};
	}
}
