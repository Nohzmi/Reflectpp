// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant.h"

#include "type.h"
#include "variant_associative_view.h"
#include "variant_sequential_view.h"

namespace reflectpp
{
	variant::~variant()
	{
		clear();
	}

	variant::variant(const variant& copy)
	{
		m_data.m_is_owner = copy.is_valid();
		m_data.m_type = copy.m_data.m_type;
		m_data.m_value = copy.is_valid() ? m_data.m_type->m_factory->m_copy(copy.m_data.m_value) : nullptr;
	}

	variant::variant(variant&& move) REFLECTPP_NOEXCEPT
	{
		m_data.m_is_owner = move.m_data.m_is_owner;
		m_data.m_type = move.m_data.m_type;
		m_data.m_value = move.m_data.m_value;

		move.m_data.m_is_owner = false;
		move.m_data.m_type = nullptr;
		move.m_data.m_value = nullptr;
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

	variant::operator details::variant_data*() const REFLECTPP_NOEXCEPT
	{
		return const_cast<details::variant_data*>(&m_data);
	}

	bool variant::can_convert(const type& target_type) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return false;

		if (m_data.m_type == static_cast<details::type_data*>(target_type))
			return true;

		if (m_data.m_type->m_is_arithmetic)
		{
			if (m_data.m_type == details::registry::get_instance().get_type<bool>()) return m_data.m_type->m_utility->m_can_convert_to_bool;
			else if (m_data.m_type == details::registry::get_instance().get_type<char>()) return m_data.m_type->m_utility->m_can_convert_to_char;
			else if (m_data.m_type == details::registry::get_instance().get_type<double>()) return m_data.m_type->m_utility->m_can_convert_to_double;
			else if (m_data.m_type == details::registry::get_instance().get_type<float>()) return m_data.m_type->m_utility->m_can_convert_to_float;
			else if (m_data.m_type == details::registry::get_instance().get_type<int>()) return m_data.m_type->m_utility->m_can_convert_to_int;
			else if (m_data.m_type == details::registry::get_instance().get_type<int8_t>()) return m_data.m_type->m_utility->m_can_convert_to_int8;
			else if (m_data.m_type == details::registry::get_instance().get_type<int16_t>()) return m_data.m_type->m_utility->m_can_convert_to_int16;
			else if (m_data.m_type == details::registry::get_instance().get_type<int32_t>()) return m_data.m_type->m_utility->m_can_convert_to_int32;
			else if (m_data.m_type == details::registry::get_instance().get_type<int64_t>()) return m_data.m_type->m_utility->m_can_convert_to_int64;
			else if (m_data.m_type == details::registry::get_instance().get_type<uint8_t>()) return m_data.m_type->m_utility->m_can_convert_to_uint8;
			else if (m_data.m_type == details::registry::get_instance().get_type<uint16_t>()) return m_data.m_type->m_utility->m_can_convert_to_uint16;
			else if (m_data.m_type == details::registry::get_instance().get_type<uint32_t>()) return m_data.m_type->m_utility->m_can_convert_to_uint32;
			else if (m_data.m_type == details::registry::get_instance().get_type<uint64_t>()) return m_data.m_type->m_utility->m_can_convert_to_uint64;
			else return false;
		}

		return is_valid() ? details::can_cast(m_data.m_type, static_cast<details::type_data*>(target_type)) : false;
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

	bool variant::convert(const type& target_type) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !can_convert(target_type))
			return false;

		if (m_data.m_type == static_cast<details::type_data*>(target_type))
			return true;

		if (m_data.m_type->m_is_arithmetic)
		{
			void* value{ nullptr };

			if (m_data.m_type == details::registry::get_instance().get_type<bool>()) value = m_data.m_type->m_utility->m_convert_to_bool(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<char>()) value = m_data.m_type->m_utility->m_convert_to_char(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<double>()) value = m_data.m_type->m_utility->m_convert_to_double(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<float>()) value = m_data.m_type->m_utility->m_convert_to_float(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<int>()) value = m_data.m_type->m_utility->m_convert_to_int(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<int8_t>()) value = m_data.m_type->m_utility->m_convert_to_int8(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<int16_t>()) value = m_data.m_type->m_utility->m_convert_to_int16(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<int32_t>()) value = m_data.m_type->m_utility->m_convert_to_int32(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<int64_t>()) value = m_data.m_type->m_utility->m_convert_to_int64(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<uint8_t>()) value = m_data.m_type->m_utility->m_convert_to_uint8(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<uint16_t>()) value = m_data.m_type->m_utility->m_convert_to_uint16(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<uint32_t>()) value = m_data.m_type->m_utility->m_convert_to_uint32(m_data.m_value);
			else if (m_data.m_type == details::registry::get_instance().get_type<uint64_t>()) value = m_data.m_type->m_utility->m_convert_to_uint64(m_data.m_value);

			if (value == nullptr)
				return false;

			if (m_data.m_is_owner)
				clear();

			m_data.m_is_owner = true;
			m_data.m_type = static_cast<details::type_data*>(target_type);
			m_data.m_value = value;
		}
		else
		{
			m_data.m_type = static_cast<details::type_data*>(target_type);
		}

		return true;
	}

	variant_associative_view variant::create_associative_view() const REFLECTPP_NOEXCEPT
	{
		return is_associative_container() ? variant_associative_view({ false, m_data.m_type, m_data.m_value }) : variant_associative_view();
	}

	variant_sequential_view variant::create_sequential_view() const REFLECTPP_NOEXCEPT
	{
		return is_sequential_container() ? variant_sequential_view({ false, m_data.m_type, m_data.m_value }) : variant_sequential_view();
	}

	type variant::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	bool variant::is_associative_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_associative_view != nullptr : false;
	}

	bool variant::is_sequential_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_sequential_view != nullptr : false;
	}

	bool variant::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}

	variant::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool variant::operator!=(const variant& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	bool variant::operator==(const variant& rhs) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !rhs.is_valid() || m_data.m_type != rhs.m_data.m_type)
			return false;

		return m_data.m_type->m_utility->m_compare(m_data.m_value, rhs.m_data.m_value);
	}
}
