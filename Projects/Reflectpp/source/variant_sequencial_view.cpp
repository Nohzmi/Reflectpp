// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_sequencial_view.h"

#include "argument.h"
#include "factory.h"
#include "type.h"
#include "variant.h"

namespace reflectpp
{
	variant_sequencial_view::iterator::iterator(size_t index, variant_sequencial_view* variant) REFLECTPP_NOEXCEPT :
		m_index{ index },
		m_variant_sequencial_view{ variant }
	{
	}

	variant variant_sequencial_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		return get_data();
	}

	variant variant_sequencial_view::iterator::get_data() const REFLECTPP_NOEXCEPT
	{
		return m_variant_sequencial_view != nullptr ? m_variant_sequencial_view->get_value(m_index) : variant();
	}

	type variant_sequencial_view::get_type() const
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	variant variant_sequencial_view::get_value(size_t index) const
	{
		return is_valid() ? variant({ false, m_data.m_type->m_value_type, m_data.m_type->m_sequence_at(m_data.m_value, index) }) : variant();
	}

	type variant_sequencial_view::get_value_type() const
	{
		return is_valid() ? type(m_data.m_type->m_value_type) : type();
	}

	variant_sequencial_view::iterator variant_sequencial_view::insert(const iterator& pos, argument value) const
	{
		if (!is_valid() || value.get_type() != get_value_type() || pos.m_index >= get_size())
			return end();

		m_data.m_type->m_sequence_insert(m_data.m_value, pos.m_index, value.m_variant->m_data.m_value);
		return begin() + pos.m_index;
	}

	void variant_sequencial_view::set_value(size_t index, argument value) const
	{
		if (!is_valid() || value.get_type() != get_value_type() || index >= get_size())
			return;

		m_data.m_type->m_sequence_assign(m_data.m_value, index, value.m_variant->m_data.m_value);
	}
}
