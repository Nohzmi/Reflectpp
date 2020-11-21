// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type_info.h"

namespace reflectpp
{
	bool type_info::operator==(const type_info& rhs) const noexcept
	{
		return m_id == rhs.m_id;
	}

	bool type_info::operator!=(const type_info& rhs) const noexcept
	{
		return m_id != rhs.m_id;
	}

	size_t type_info::get_id() const noexcept
	{
		return m_id;
	}

	const char* type_info::get_name() const noexcept
	{
		return m_name;
	}

	type_info::type_info(size_t id, const char* name) noexcept :
		m_id{ id },
		m_name{ name }
	{
	}
}
