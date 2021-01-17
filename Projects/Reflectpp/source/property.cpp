// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "property.h"

#include "argument.h"
#include "instance.h"
#include "type.h"

namespace reflectpp
{
	property::property(details::property_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	bool property::operator==(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data == rhs.m_data;
	}

	bool property::operator!=(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	property::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	type property::get_declaring_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_type) : type();
	}

	size_t property::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_id : 0;
	}

	const char* property::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_name : "";
	}

	size_t property::get_specifiers() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_specifiers : 0;
	}

	type property::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_property_type) : type();
	}

	variant property::get_value(instance object) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !object.is_valid() || object.get_type() != get_declaring_type())
			return variant();

		bool is_owner{ false };
		void* value{ m_data->m_getter(object.get_raw_data(), is_owner) };

		return variant({ is_owner, m_data->m_property_type, value });
	}

	bool property::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}

	void property::set_value(instance object, argument arg) const REFLECTPP_NOEXCEPT
	{
		if (is_valid() && object.is_valid() && object.get_type() == get_declaring_type() && arg.get_type() == get_type())
			m_data->m_setter(object.get_raw_data(), arg.get_raw_data());
	}
}
