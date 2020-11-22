#include "..\..\property.h"
// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE variant property::get_value(T* object) const
	{
		//REFLECTPP_ASSERT(details::registry::get_instance().get_type(object) == m_type, "wrong object type, %s is in type", m_name);
		REFLECTPP_ASSERT(details::registry::get_instance().get_type(object) == m_type, "wrong object type");

		if (m_getter != nullptr)
		{
			bool is_owner{ false };
			void* data{ m_getter(object, is_owner) };

			return variant(data, is_owner, m_property_type);
		}
		else
			return variant(reinterpret_cast<char*>(object) + m_offset, false, m_property_type);
	}
}
