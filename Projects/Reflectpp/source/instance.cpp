// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "instance.h"

#include "type.h"

namespace reflectpp
{
	instance::~instance()
	{
		if (m_is_owner && m_variant != nullptr)
		{
			delete m_variant;
			m_variant = nullptr;
		}
	}

	instance::instance(const instance& copy)
	{
		*this = copy;
	}

	instance& instance::operator=(const instance& copy)
	{
		m_variant = copy.m_variant;
		return *this;
	}

	instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ const_cast<variant*>(&var) }
	{
	}

	instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	void* instance::get_raw_data() REFLECTPP_NOEXCEPT
	{
		return m_variant->get_raw_data();
	}

	type instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant->get_type();
	}

	bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_variant->is_valid();
	}
}
