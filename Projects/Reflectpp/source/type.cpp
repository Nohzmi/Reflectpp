// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type.h"

#include "enumeration.h"
#include "factory.h"
#include "property.h"
#include "type_info.h"
#include "variant.h"

namespace reflectpp
{
	type::type(details::type_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	type::operator details::type_data*() const REFLECTPP_NOEXCEPT
	{
		return m_data;
	}

	variant type::create() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? variant({ true, m_data, m_data->m_factory->m_constructor() }) : variant();
	}

	bool type::destroy(variant& var) const REFLECTPP_NOEXCEPT
	{
		if (is_valid() && var.get_type().get_id() == m_data->m_type_info->m_id)
		{
			var.clear();
			return true;
		}

		return false;
	}

	std::vector<type> type::get_base_classes() const REFLECTPP_NOEXCEPT
	{
		std::vector<type> base_types;

		if (!is_valid())
			return base_types;

		for (auto& it : m_data->m_base_types)
			base_types.emplace_back(type(it));

		return base_types;
	}

	type type::get_by_name(const char* name) REFLECTPP_NOEXCEPT
	{
		return type(details::registry::get_instance().get_type_by_name(name));
	}

	std::vector<type> type::get_derived_classes() const REFLECTPP_NOEXCEPT
	{
		std::vector<type> derived_types;

		if (!is_valid())
			return derived_types;

		for (auto& it : m_data->m_derived_types)
			derived_types.emplace_back(type(it));

		return derived_types;
	}

	enumeration type::get_enumeration() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? enumeration(m_data) : enumeration();
	}

	factory type::get_factory() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? factory(m_data->m_factory) : factory();
	}

	size_t type::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_type_info->m_id : 0;
	}

	const char* type::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_type_info->m_name : "";
	}

	property type::get_property(const char* name) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return property();

		size_t id{ details::hash(name) };

		for (auto& it : m_data->m_properties)
			if (it->m_id == id)
				return (it->m_specifiers & Exposed) > 0 ? property(it) : property();

		return property();
	}

	std::vector<property> type::get_properties() const REFLECTPP_NOEXCEPT
	{
		std::vector<property> properties;

		if (!is_valid())
			return properties;

		for (auto& it : m_data->m_properties)
			if ((it->m_specifiers & Exposed) > 0)
				properties.emplace_back(property(it));

		return properties;
	}

	size_t type::get_sizeof() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_size : 0;
	}

	type_info type::get_type_info() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type_info(m_data->m_type_info) : type_info();
	}

	std::vector<type> type::get_types() REFLECTPP_NOEXCEPT
	{
		std::vector<type> types;

		for (auto& it : details::registry::get_instance().get_types())
			types.emplace_back(type(it));

		return types;
	}

	bool type::is_arithmetic() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_is_arithmetic : false;
	}

	bool type::is_associative_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_associative_view != nullptr : false;
	}

	bool type::is_base_of(const type& other) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !other.is_valid())
			return false;

		for (auto& it : get_derived_classes())
			if (it.m_data == other.m_data)
				return true;

		return false;
	}

	bool type::is_boolean() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_is_boolean : false;
	}

	bool type::is_class() const REFLECTPP_NOEXCEPT
	{
		return !is_arithmetic() && !is_associative_container() && !is_enumeration() && !is_sequential_container() && !is_wrapper();
	}

	bool type::is_derived_of(const type& other) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !other.is_valid())
			return false;

		for (auto& it : get_base_classes())
			if (it.m_data == other.m_data)
				return true;

		return false;
	}

	bool type::is_enumeration() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_enumeration != nullptr : false;
	}

	bool type::is_floating_point() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_is_floating_point : false;
	}

	bool type::is_integral() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_is_integral : false;
	}

	bool type::is_sequential_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_sequential_view != nullptr : false;
	}

	bool type::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}

	bool type::is_wrapper() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_wrapper_view != nullptr : false;
	}

	type::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool type::operator!=(const type& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	bool type::operator==(const type& rhs) const REFLECTPP_NOEXCEPT
	{
		return is_valid() && rhs.is_valid() ? m_data == rhs.m_data : false;
	}
}
