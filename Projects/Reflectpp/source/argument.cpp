// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "argument.h"

#include "type.h"

namespace reflectpp
{
	argument::~argument()
	{
		if (m_is_owner && m_variant != nullptr)
		{
			delete m_variant;
			m_variant = nullptr;
		}
	}

	argument::argument(const argument& copy)
	{
		*this = copy;
	}

	argument& argument::operator=(const argument& copy)
	{
		m_variant = copy.m_variant;
		return *this;
	}

	argument::argument(variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ &var }
	{
	}

	argument::argument(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ const_cast<variant*>(&var) }
	{
	}

	void* argument::get_raw_data() REFLECTPP_NOEXCEPT
	{
		return m_variant->get_raw_data();
	}

	type argument::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant->get_type();
	}
}
