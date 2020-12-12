// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "argument.h"

#include "type.h"

namespace reflectpp
{
	argument::~argument()
	{
		if (m_is_owner && m_var != nullptr)
		{
			delete m_var;
			m_var = nullptr;
		}
	}

	argument::argument(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_var{ const_cast<variant*>(&var) }
	{
	}

	type& argument::get_type() const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(m_var != nullptr && m_var->is_valid(), "invalid argument");
		return m_var->get_type();
	}
}
