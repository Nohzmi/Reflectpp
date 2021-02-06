// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "property.h"

#include "argument.h"
#include "instance.h"
#include "type.h"

namespace reflectpp
{
	property::property(details::property_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	type property::get_declaring_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_declaring_type) : type();
	}

	size_t property::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_id : 0;
	}

	const char* property::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_name : "";
	}

	size_t property::get_specifiers() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_specifiers : 0;
	}

	type property::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_type) : type();
	}

	variant property::get_value(instance object) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return variant();

		auto object_var{ static_cast<variant*>(object) };

		if (object_var == nullptr || !object_var->is_valid() || !object_var->convert(get_declaring_type()))
			return variant();

		bool is_owner{ false };
		void* object_ptr{ static_cast<details::variant_data*>(*object_var)->m_value };
		void* value{ m_data->m_getter(object_ptr, is_owner) };

		return variant({ is_owner, m_data->m_type, value });
	}

	bool property::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}

	property::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool property::operator!=(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	bool property::operator==(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return is_valid() && rhs.is_valid() ? m_data == rhs.m_data : false;
	}

	bool property::set_value(instance object, argument arg) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return false;

		auto object_var{ static_cast<variant*>(object) };
		auto arg_var{ static_cast<variant*>(arg) };

		if (object_var == nullptr || !object_var->is_valid() || !object_var->convert(get_declaring_type()))
			return false;

		if (arg_var == nullptr || !arg_var->is_valid() || !arg_var->convert(get_type()))
			return false;

		void* object_ptr{ static_cast<details::variant_data*>(*object_var)->m_value };
		void* arg_ptr{ static_cast<details::variant_data*>(*arg_var)->m_value };

		m_data->m_setter(object_ptr, arg_ptr);
		return true;
	}
}
