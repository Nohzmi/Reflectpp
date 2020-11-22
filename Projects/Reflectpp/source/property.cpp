// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "property.h"

#include "type.h"

namespace reflectpp
{
	size_t property::get_id() const REFLECTPP_NOEXCEPT
	{
		return m_id;
	}

	const char* property::get_name() const REFLECTPP_NOEXCEPT
	{
		return m_name;
	}

	size_t property::get_offset() const REFLECTPP_NOEXCEPT
	{
		return m_offset;
	}

	type& property::get_type() const REFLECTPP_NOEXCEPT
	{
		return *m_property_type;
	}

	variant property::get_value(const variant& object) const
	{
		REFLECTPP_ASSERT(*object.m_type == *m_type, "wrong object type");
		//REFLECTPP_ASSERT(*object.m_type == *m_type, "wrong object type, %s is in %s\n", m_name, m_type->get_name());

		if (m_getter != nullptr)
		{
			bool is_owner{ false };
			void* data{ m_getter(object.m_data, is_owner) };

			return variant(data, is_owner, m_property_type);
		}
		else
			return variant(static_cast<char*>(object.m_data) + m_offset, false, m_property_type);
	}

	property::property(GetterT getter, size_t id, const char* name, size_t offset, type* property_type, SetterT setter, type* type) REFLECTPP_NOEXCEPT :
		m_getter{ getter },
		m_id{ id },
		m_name{ name },
		m_offset{ offset },
		m_property_type{ property_type },
		m_setter{ setter },
		m_type{ type }
	{
	}
}
