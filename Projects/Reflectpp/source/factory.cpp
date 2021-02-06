// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "factory.h"

namespace reflectpp
{
	factory::factory(details::factory_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	void* factory::construct() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_constructor() : nullptr;
	}

	void* factory::copy(void* object) const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_copy(object) : nullptr;
	}

	void factory::destroy(void* object) const REFLECTPP_NOEXCEPT
	{
		if (is_valid())
			m_data->m_destructor(object);
	}

	bool factory::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}

	factory::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}
}
