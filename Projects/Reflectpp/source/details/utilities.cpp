// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/utilities.h"

#include "type.h"

namespace reflectpp
{
	namespace details
	{
		namespace utilities
		{
			size_t type_id(const type* type) REFLECTPP_NOEXCEPT
			{
				return type->get_id();
			}

			const char* type_name(const type* type) REFLECTPP_NOEXCEPT
			{
				return type->get_name();
			}
		}
	}
}
