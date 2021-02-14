// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_wrapper_view.h"

#include "argument.h"
#include "type.h"

namespace reflectpp
{
	variant_wrapper_view::variant_wrapper_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	type variant_wrapper_view::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	type variant_wrapper_view::get_wrapped_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_wrapper_view->m_wrapped_type) : type();
	}

	variant variant_wrapper_view::get_wrapped_value() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return variant();

		auto get{ m_data.m_type->m_wrapper_view->m_get(m_data.m_value) };
		return variant({ false, get.first, get.second });
	}

	bool variant_wrapper_view::is_empty() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? !get_wrapped_value().is_valid() : false;
	}

	bool variant_wrapper_view::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr && m_data.m_type->m_wrapper_view != nullptr;
	}

	variant_wrapper_view::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	void variant_wrapper_view::reset(argument value) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_wrapper_view->m_reset == nullptr)
			return;

		auto value_var{ static_cast<variant*>(value) };

		if (value_var == nullptr || !value_var->is_valid())
		{
			m_data.m_type->m_wrapper_view->m_reset(m_data.m_value, nullptr);
			return;
		}

		if (!value_var->can_convert(get_wrapped_type()))
			return;

		if (!static_cast<details::variant_data*>(*value_var)->m_is_owner)
			*value_var = variant(*value_var);

		value_var->convert(get_wrapped_type());
		static_cast<details::variant_data*>(*value_var)->m_is_owner = false;
		void* value_ptr{ static_cast<details::variant_data*>(*value_var)->m_value };
		m_data.m_type->m_wrapper_view->m_reset(m_data.m_value, value_ptr);
	}
}
