// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct variant_data final
		{
			bool m_is_owner{ false };
			type_data* m_type{ nullptr };
			void* m_value{ nullptr };
		};
	}
}
