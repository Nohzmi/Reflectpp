// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/platform.h"

namespace reflectpp
{
	namespace details
	{
		struct type_data;

		struct REFLECTPP_API variant_data final
		{
			bool m_is_owner{ false };
			type_data* m_type{nullptr};
			void* m_value{ nullptr };

		public:
			variant_data() = default;
			~variant_data() = default;
		};
	}
}
