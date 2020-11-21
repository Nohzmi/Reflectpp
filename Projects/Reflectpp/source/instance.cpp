// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "instance.h"

#include "type.h"

namespace reflectpp
{
	instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_var{ var }
	{
	}
			
	instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	type& instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_var.get_type();
	}

	bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_var.is_valid();
	}
}
