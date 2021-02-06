// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/reflectpp_cast_helper.h"

namespace reflectpp
{
	namespace details
	{
		bool can_cast(type_data* object, type_data* type) REFLECTPP_NOEXCEPT
		{
			if (type->m_hierarchy_id != object->m_hierarchy_id)
				return false;

			auto isBaseOf = [](type_data* object, type_data* type, auto& lambda) -> bool
			{
				if (object == type)
					return true;

				bool res{ false };

				for (auto& it : object->m_base_types)
					res |= lambda(it, type, lambda);

				return res;
			};

			return isBaseOf(object, type, isBaseOf);
		}
	}
}
