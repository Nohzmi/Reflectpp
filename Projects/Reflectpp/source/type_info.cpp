// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type_info.h"

namespace reflectpp
{
	bool type_info::operator==(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_id == rhs.m_id;
	}

	bool type_info::operator!=(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_id != rhs.m_id;
	}

	size_t type_info::get_id() const REFLECTPP_NOEXCEPT
	{
		return m_id;
	}

	const char* type_info::get_name() const REFLECTPP_NOEXCEPT
	{
		return m_name;
	}

	type_info::type_info(size_t id, const char* name) REFLECTPP_NOEXCEPT :
		m_id{ id },
		m_name{ name }
	{
	}
}
