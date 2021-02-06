// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "enumeration.h"

#include <string>
#include "type.h"
#include "argument.h"

namespace reflectpp
{
	enumeration::enumeration(details::type_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	const char* enumeration::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_enumeration->m_name : nullptr;
	}

	std::vector<const char*> enumeration::get_names() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_enumeration->m_names : std::vector<const char*>();
	}

	type enumeration::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data) : type();
	}

	type enumeration::get_underlying_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data->m_enumeration->m_underlying_type) : type();
	}

	std::vector<variant> enumeration::get_values() const REFLECTPP_NOEXCEPT
	{
		std::vector<variant> values;

		if (!is_valid())
			return values;

		for (auto& it : m_data->m_enumeration->m_values)
			values.emplace_back(variant({ false, m_data->m_enumeration->m_underlying_type, it }));

		return values;
	}

	bool enumeration::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr && m_data->m_enumeration != nullptr;
	}

	variant enumeration::name_to_value(const char* name) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || name == nullptr)
			return variant();

		for (int i = 0; i < m_data->m_enumeration->m_names.size(); ++i)
			if (std::string(m_data->m_enumeration->m_names[i]) == std::string(name))
				return variant({ false, m_data->m_enumeration->m_underlying_type, m_data->m_enumeration->m_values[i] });

		return variant();
	}

	bool enumeration::operator!=(const enumeration& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	bool enumeration::operator==(const enumeration& rhs) const REFLECTPP_NOEXCEPT
	{
		return is_valid() && rhs.is_valid() ? m_data == rhs.m_data : false;
	}

	enumeration::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	const char* enumeration::value_to_name(argument value) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return "";

		auto value_var{ static_cast<variant*>(value) };

		if (value_var == nullptr || !value_var->is_valid() || !value_var->convert(get_type()))
			return "";

		void* value_ptr{ static_cast<details::variant_data*>(*value_var)->m_value };

		for (int i = 0; i < m_data->m_enumeration->m_values.size(); ++i)
			if (m_data->m_utility->m_compare(m_data->m_enumeration->m_values[i], value_ptr))
				return m_data->m_enumeration->m_names[i];

		return "";
	}
}
