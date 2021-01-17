// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_sequencial_view.h"

#include "argument.h"
#include "type.h"

namespace reflectpp
{
	variant_sequencial_view::iterator::iterator(size_t index, variant_sequencial_view* variant) REFLECTPP_NOEXCEPT :
		m_index{ index },
		m_variant_sequencial_view{ variant }
	{
	}

	bool variant_sequencial_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index == rhs.m_index) && (m_variant_sequencial_view == rhs.m_variant_sequencial_view);
	}

	bool variant_sequencial_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator++(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		++(*this);
		return it;
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator--() REFLECTPP_NOEXCEPT
	{
		--m_index;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator--(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		--(*this);
		return it;
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator+=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator+(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it += i;
		return it;
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator-=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator-(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it -= i;
		return it;
	}

	variant variant_sequencial_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		return get_data();
	}

	variant variant_sequencial_view::iterator::get_data() const REFLECTPP_NOEXCEPT
	{
		return m_variant_sequencial_view != nullptr ? m_variant_sequencial_view->get_value(m_index) : variant();
	}

	size_t variant_sequencial_view::iterator::get_index() const REFLECTPP_NOEXCEPT
	{
		return m_index;
	}

	variant_sequencial_view::variant_sequencial_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	variant_sequencial_view::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	variant_sequencial_view::iterator variant_sequencial_view::begin() const REFLECTPP_NOEXCEPT
	{
		return iterator(0, const_cast<variant_sequencial_view*>(this));
	}

	void variant_sequencial_view::clear() REFLECTPP_NOEXCEPT
	{
		if (is_valid())
			m_data.m_type->m_sequence_clear(m_data.m_value);
	}

	variant_sequencial_view::iterator variant_sequencial_view::end() const REFLECTPP_NOEXCEPT
	{
		return iterator(get_size(), const_cast<variant_sequencial_view*>(this));
	}

	variant_sequencial_view::iterator variant_sequencial_view::erase(const iterator& pos) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || pos.get_index() >= get_size())
			return end();

		m_data.m_type->m_sequence_erase(m_data.m_value, pos.get_index());
		return begin() + pos.get_index();
	}

	size_t variant_sequencial_view::get_size() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_sequence_size(m_data.m_value) : 0;
	}

	type variant_sequencial_view::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	variant variant_sequencial_view::get_value(size_t index) const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? variant({ false, m_data.m_type->m_value_type, m_data.m_type->m_sequence_at(m_data.m_value, index) }) : variant();
	}

	type variant_sequencial_view::get_value_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_value_type) : type();
	}

	variant_sequencial_view::iterator variant_sequencial_view::insert(const iterator& pos, argument value) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || value.get_type() != get_value_type() || pos.get_index() >= get_size())
			return end();

		m_data.m_type->m_sequence_insert(m_data.m_value, pos.get_index(), value.get_raw_data());
		return begin() + pos.get_index();
	}

	bool variant_sequencial_view::is_empty() const REFLECTPP_NOEXCEPT
	{
		return get_size() == 0;
	}

	bool variant_sequencial_view::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}

	void variant_sequencial_view::set_size(size_t size) const REFLECTPP_NOEXCEPT
	{
		if (is_valid())
			m_data.m_type->m_sequence_resize(m_data.m_value, size);
	}

	void variant_sequencial_view::set_value(size_t index, argument value) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || value.get_type() != get_value_type() || index >= get_size())
			return;

		m_data.m_type->m_sequence_assign(m_data.m_value, index, value.get_raw_data());
	}
}
