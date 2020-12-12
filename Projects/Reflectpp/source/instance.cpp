// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "instance.h"

#include "type.h"

namespace reflectpp
{
	instance::~instance()
	{
		if (m_is_owner && m_var != nullptr)
		{
			delete m_var;
			m_var = nullptr;
		}
	}

	instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_var{ const_cast<variant*>(&var) }
	{
	}

	instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	type& instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_var->get_type();
	}

	bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_var->is_valid();
	}
}
