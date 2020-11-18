// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/utilities.h"
#include "type.h"

namespace reflectpp
{
	template<typename T>
	inline variant property::get_value(T* object) const
	{
		details::_assert(type::Get(object) == *m_type, "property::get_value(%s*& object) : wrong object type, %s is in %s\n", details::type_name(object), m_name, m_type->get_name());

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
