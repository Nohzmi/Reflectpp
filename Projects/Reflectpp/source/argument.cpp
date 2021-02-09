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

	argument::argument(const argument& copy) :
		m_is_owner { copy.m_variant != nullptr },
		m_variant{ copy.m_variant != nullptr ? new variant(*copy.m_variant) : nullptr }
	{
	}

	argument::argument(argument&& move) REFLECTPP_NOEXCEPT :
		m_is_owner{ move.m_is_owner },
		m_variant{ move.m_variant }
	{
		move.m_is_owner = false;
		move.m_variant = nullptr;
	}

	argument& argument::operator=(const argument& copy)
	{
		m_is_owner = copy.m_variant != nullptr;
		m_variant = copy.m_variant != nullptr ? new variant(*copy.m_variant) : nullptr;

		return *this;
	}

	argument& argument::operator=(argument&& move) REFLECTPP_NOEXCEPT
	{
		m_is_owner = move.m_is_owner;
		m_variant = move.m_variant;

		move.m_is_owner = false;
		move.m_variant = nullptr;

		return *this;
	}

	argument::operator variant*() const REFLECTPP_NOEXCEPT
	{
		return m_variant;
	}

	argument::argument(variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ nullptr }
	{
		details::variant_data* data{ static_cast<details::variant_data*>(var) };
		m_variant = new variant({ false, data->m_type, data->m_value });
	}

	argument::argument(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ nullptr }
	{
		details::variant_data* data{ static_cast<details::variant_data*>(var) };
		m_variant = new variant({ false, data->m_type, data->m_value });
	}

	type argument::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->get_type() : type();
	}
}
