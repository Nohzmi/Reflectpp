// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant.h"

#include "type.h"
#include "variant_associative_view.h"
#include "variant_sequencial_view.h"

namespace reflectpp
{
	variant::~variant()
	{
		clear();
	}

	variant::variant(const variant& copy)
	{
		*this = copy;
	}

	variant::variant(variant&& move) REFLECTPP_NOEXCEPT
	{
		*this = std::move(move);
	}

	variant& variant::operator=(const variant& copy)
	{
		m_data.m_is_owner = copy.is_valid();
		m_data.m_type = copy.m_data.m_type;
		m_data.m_value = copy.is_valid() ? m_data.m_type->m_factory->m_copy(copy.m_data.m_value) : nullptr;
		return *this;
	}

	variant& variant::operator=(variant&& move) REFLECTPP_NOEXCEPT
	{
		m_data.m_is_owner = move.m_data.m_is_owner;
		m_data.m_type = move.m_data.m_type;
		m_data.m_value = move.m_data.m_value;

		move.m_data.m_is_owner = false;
		move.m_data.m_type = nullptr;
		move.m_data.m_value = nullptr;

		return *this;
	}

	variant::variant(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	bool variant::operator==(const variant& rhs) const REFLECTPP_NOEXCEPT
	{
		return is_valid() && rhs.is_valid() ? m_data.m_type == rhs.m_data.m_type && m_data.m_value == rhs.m_data.m_value : false;
	}

	bool variant::operator!=(const variant& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	variant::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	void variant::clear() REFLECTPP_NOEXCEPT
	{
		if (m_data.m_is_owner && is_valid())
		{
			m_data.m_type->m_factory->m_destructor(m_data.m_value);
			m_data.m_value = nullptr;
		}

		m_data = details::variant_data();
	}

	variant_associative_view variant::create_associative_view() const REFLECTPP_NOEXCEPT
	{
		return is_associative_container() ? variant_associative_view({ false, m_data.m_type, m_data.m_value }) : variant_associative_view();
	}

	variant_sequencial_view variant::create_sequential_view() const REFLECTPP_NOEXCEPT
	{
		return is_sequential_container() ? variant_sequencial_view({ false, m_data.m_type, m_data.m_value }) : variant_sequencial_view();
	}

	void* variant::get_raw_data() REFLECTPP_NOEXCEPT
	{
		return m_data.m_value;
	}

	type variant::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	bool variant::is_associative_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_is_associative_container : false;
	}

	bool variant::is_sequential_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_is_sequence_container : false;
	}

	bool variant::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}
}
