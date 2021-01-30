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

	instance::instance(const instance& copy) :
		m_is_owner{ copy.m_variant != nullptr },
		m_variant{ copy.m_variant != nullptr ? new variant(*copy.m_variant) : nullptr }
	{
	}

	instance::instance(instance&& move) REFLECTPP_NOEXCEPT :
		m_is_owner{ move.m_is_owner },
		m_variant{ move.m_variant }
	{
		move.m_is_owner = false;
		move.m_variant = nullptr;
	}


	instance& instance::operator=(const instance& copy)
	{
		m_is_owner = copy.m_variant != nullptr;
		m_variant = copy.m_variant != nullptr ? new variant(*copy.m_variant) : nullptr;

		return *this;
	}

	instance& instance::operator=(instance&& move) REFLECTPP_NOEXCEPT
	{
		m_is_owner = move.m_is_owner;
		m_variant = move.m_variant;

		move.m_is_owner = false;
		move.m_variant = nullptr;

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
		return m_variant != nullptr ? m_variant->get_raw_data() : nullptr;
	}

	type instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->get_type() : type();
	}

	bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->is_valid() : false;
	}
}
