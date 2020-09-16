// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "property.h"
#include "type.h"

size_t property::get_id() const noexcept
{
	return m_id;
}

const char* property::get_name() const noexcept
{
	return m_name;
}

size_t property::get_offset() const noexcept
{
	return m_offset;
}

type& property::get_type() const noexcept
{
	return *m_property_type;
}

variant property::get_value(const variant& object) const
{
	//Reflectpp::Assert(*object.m_Type == *m_Type, "property::GetValue(Variant& object) : wrong object type, %s is in %s\n", m_Name, m_Type->GetName());

	if (m_getter != nullptr)
	{
		bool isOwner{ false };
		void* data{ m_getter(object.m_data, isOwner) };

		return variant(data, isOwner, m_property_type);
	}
	else
		return variant(static_cast<char*>(object.m_data) + m_offset, false, m_property_type);
}

property::property(GetterT getter, size_t id, const char* name, size_t offset, type* property_type, SetterT setter, type* type) noexcept :
	m_getter{ getter },
	m_id{ id },
	m_name{ name },
	m_offset{ offset },
	m_property_type{ property_type },
	m_setter{ setter },
	m_type{ type }
{
}