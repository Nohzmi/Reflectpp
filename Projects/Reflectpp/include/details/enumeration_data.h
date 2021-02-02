// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory_data.h
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
		struct enumeration_data final
		{
			type_data* m_declaring_type{ nullptr };
			const char* m_name;
			std::vector<const char*> m_names;
			type_data* m_underlying_type{ nullptr };
			std::vector<size_t> m_values;
		};
	}
}
