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
			associative_view_data* m_associative_view{ nullptr };
			std::vector<type_data*> m_base_types;
			std::vector<type_data*> m_derived_types;
			factory_data* m_factory{ nullptr };
			size_t m_hierarchy_id{ 0 };
			bool m_is_arithmetic{ false };
			std::vector<property_data*> m_properties;
			sequential_view_data* m_sequential_view{ nullptr };
			size_t m_size{ 0 };
			type_info_data* m_type_info{ nullptr };
		};
	}
}
