// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

#include "details/forward.h"
#include "details/platform.h"

namespace reflectpp
{
	namespace details
	{
		struct factory_data;
		struct property_data;
		struct type_info_data;

		struct REFLECTPP_API type_data final
		{
			std::vector<type_data*> m_base_types;
			std::vector<type_data*> m_derived_types;
			factory_data* m_factory{ nullptr };
			size_t m_hierarchy_id{ 0 };
			bool m_is_associative_container{ false };
			bool m_is_sequence_container{ false };
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
