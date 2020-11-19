// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "type.h"

#include "factory.h"
#include "property.h"
#include "type_info.h"

namespace reflectpp
{

	bool type::operator==(const type& rhs) const noexcept
	{
		return m_type_info == rhs.m_type_info;
	}

	bool type::operator!=(const type& rhs) const noexcept
	{
		return m_type_info != rhs.m_type_info;
	}

	variant type::create() const
	{
		return variant(get_factory().construct(), true, const_cast<type*>(this));
	}

	range<type>& type::get_base_classes() const noexcept
	{
		return *const_cast<range<type>*>(&m_base_types);
	}

	range<type>& type::get_derived_classes() const noexcept
	{
		return *const_cast<range<type>*>(&m_derived_types);
	}

	factory& type::get_factory() const noexcept
	{
		return *m_factory;
	}

	size_t type::get_id() const noexcept
	{
		return m_type_info->get_id();
	}

	const char* type::get_name() const noexcept
	{
		return m_type_info->get_name();
	}

	property& type::get_property(const char* name) const noexcept
	{
		size_t id{ details::hash(name) };

		for (auto& prop : m_properties)
			if (prop.get_id() == id)
				return prop;

		REFLECTPP_ASSERT(false, "type::get_property(const char* name) : %s isn't registered\n", name);
		return *m_properties.begin();
	}

	range<property>& type::get_properties() const noexcept
	{
		return *const_cast<range<property>*>(&m_properties);
	}

	size_t type::get_sizeof() const noexcept
	{
		return m_size;
	}

	type_info& type::get_type_info() const noexcept
	{
		return *m_type_info;
	}

	type::type(factory* factory, size_t size, type_info* type_info) noexcept :
		m_factory{ factory },
		m_hierarchy_id{ type_info->get_id() },
		m_size{ size },
		m_type_info{ type_info }
	{
	}
}
