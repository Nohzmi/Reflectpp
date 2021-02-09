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

	instance::operator variant*() const REFLECTPP_NOEXCEPT
	{
		return m_variant;
	}

	instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ nullptr }
	{
		details::variant_data* data{ static_cast<details::variant_data*>(var) };
		m_variant = new variant({ false, data->m_type, data->m_value });
	}

	type instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->get_type() : type();
	}

	instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->is_valid() : false;
	}
}
