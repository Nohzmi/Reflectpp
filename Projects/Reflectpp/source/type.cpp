// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type.h"

#include "factory.h"
#include "property.h"
#include "type_info.h"
#include "variant.h"

namespace reflectpp
{
	variant type::create() const REFLECTPP_NOEXCEPT
	{
		return variant({ true, m_data, m_data->m_factory->m_constructor() });
	}

	std::vector<type> type::get_base_classes() const REFLECTPP_NOEXCEPT
	{
		std::vector<type> base_types;

		if (!is_valid())
			return base_types;

		for (auto it : m_data->m_base_types)
			base_types.emplace_back(type(it));

		return base_types;
	}

	std::vector<type> type::get_derived_classes() const REFLECTPP_NOEXCEPT
	{
		std::vector<type> derived_types;

		if (!is_valid())
			return derived_types;

		for (auto it : m_data->m_derived_types)
			derived_types.emplace_back(type(it));

		return derived_types;
	}

	factory type::get_factory() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? factory(m_data->m_factory) : factory();
	}

	property type::get_property(const char* name) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return property();

		size_t id{ details::hash(name) };

		for (auto it : m_data->m_properties)
			if (it->m_id == id)
				return (it->m_specifiers & Exposed) > 0 ? property(it) : property();

		return property();
	}

	std::vector<property> type::get_properties() const REFLECTPP_NOEXCEPT
	{
		std::vector<property> properties;

		if (!is_valid())
			return properties;

		for (auto it : m_data->m_properties)
			if ((it->m_specifiers & Exposed) > 0)
				properties.emplace_back(property(it));

		return properties;
	}

	type_info type::get_type_info() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type_info(m_data->m_type_info) : type_info();
	}
}
