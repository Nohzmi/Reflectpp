// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "property.h"

#include "type.h"

#include "variant.h"
#include "instance.h"
#include "argument.h"

namespace reflectpp
{
	type property::get_declaring_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_type) : type();
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
		void* value{ m_data->m_getter(object.m_variant.m_data.m_value, is_owner) };

		return variant({ is_owner, m_data->m_property_type, value });
	}

	void property::set_value(instance object, argument arg) const REFLECTPP_NOEXCEPT
	{
		if (is_valid() && object.is_valid() && object.get_type() == get_declaring_type() && arg.get_type() == get_type())
			m_data->m_setter(object.m_variant.m_data.m_value, arg.m_variant.m_data.m_value);
	}
}
