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

	size_t property::get_specifiers() const REFLECTPP_NOEXCEPT
	{
		return m_specifiers;
	}

	type& property::get_type() const REFLECTPP_NOEXCEPT
	{
		return *m_property_type;
	}

	variant property::get_value(const instance& object) const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(object.is_valid(), "invalid instance");
		REFLECTPP_ASSERT(object.m_var->m_type == m_type, "wrong object type");

		bool is_owner{ false };
		void* data{ m_getter(object.m_var->m_data, is_owner) };

		return variant(data, is_owner, m_property_type);
	}

	void property::set_value(const instance& object, const argument& arg) const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(object.is_valid(), "invalid instance");
		REFLECTPP_ASSERT(object.m_var->m_type == m_type, "wrong object type");
		REFLECTPP_ASSERT(arg.m_var->m_type == m_property_type, "wrong argument type");

		m_setter(object.m_var->m_data, arg.m_var->m_data);
	}

	property::property(GetterT getter, size_t id, const char* name, type* property_type, SetterT setter, size_t specifiers, type* type) REFLECTPP_NOEXCEPT :
		m_getter{ getter },
		m_id{ id },
		m_name{ name },
		m_property_type{ property_type },
		m_setter{ setter },
		m_specifiers{ specifiers },
		m_type{ type }
	{
	}
}
