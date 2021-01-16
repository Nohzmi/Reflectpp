// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/forward.h"
#include "details/platform.h"

namespace reflectpp
{
	namespace details
	{
		struct type_data;

		struct REFLECTPP_API property_data final
		{
			Getter m_getter{ nullptr };
			size_t m_id{ 0 };
			const char* m_name{ "" };
			type_data* m_property_type{ nullptr };
			Setter m_setter{ nullptr };
			size_t m_specifiers{ 0 };
			type_data* m_type{ nullptr };

		public:
			property_data() = default;
			~property_data() = default;
		};
	}
}