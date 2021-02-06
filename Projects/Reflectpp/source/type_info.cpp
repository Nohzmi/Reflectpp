// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type_info.h"

namespace reflectpp
{
	type_info::type_info(details::type_info_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	size_t type_info::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_id : 0;
	}

	const char* type_info::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_name : "";
	}

	bool type_info::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}

	type_info::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool type_info::operator!=(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	bool type_info::operator==(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return is_valid() && rhs.is_valid() ? m_data == rhs.m_data : false;
	}
}
