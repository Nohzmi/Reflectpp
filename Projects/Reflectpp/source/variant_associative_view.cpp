// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_associative_view.h"

#include "argument.h"
#include "type.h"

namespace reflectpp
{
	variant_associative_view::iterator::iterator(size_t index, variant_associative_view* variant) REFLECTPP_NOEXCEPT :
		m_index{ index },
		m_variant_associative_view{ variant }
	{
	}

	bool variant_associative_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index == rhs.m_index) && (m_variant_associative_view == rhs.m_variant_associative_view);
	}

	bool variant_associative_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	variant_associative_view::iterator& variant_associative_view::iterator::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator++(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		++(*this);
		return it;
	}

	variant_associative_view::iterator& variant_associative_view::iterator::operator--() REFLECTPP_NOEXCEPT
	{
		--m_index;
		return *this;
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator--(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		--(*this);
		return it;
	}

	variant_associative_view::iterator& variant_associative_view::iterator::operator+=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator+(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it += i;
		return it;
	}

	variant_associative_view::iterator& variant_associative_view::iterator::operator-=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator-(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it -= i;
		return it;
	}

	std::pair<variant, variant> variant_associative_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		////////////////////////////////////////////////////////////////////////////////////
		//return std::make_pair(variant);
		return std::pair<variant, variant>();
	}

	variant variant_associative_view::iterator::get_data() const REFLECTPP_NOEXCEPT
	{
		////////////////////////////////////////////////////////////////////////////////////
		//return m_variant_associative_view != nullptr ? m_variant_associative_view->get_value(m_index) : variant();
		return variant();
	}

	size_t variant_associative_view::iterator::get_index() const REFLECTPP_NOEXCEPT
	{
		return m_index;
	}

	variant_associative_view::variant_associative_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	variant_associative_view::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	variant_associative_view::iterator variant_associative_view::begin() const REFLECTPP_NOEXCEPT
	{
		return iterator(0, const_cast<variant_associative_view*>(this));
	}

	void variant_associative_view::clear() REFLECTPP_NOEXCEPT
	{
		if (is_valid())
			m_data.m_type->m_associative_clear(m_data.m_value);
	}

	variant_associative_view::iterator variant_associative_view::end() const REFLECTPP_NOEXCEPT
	{
		return iterator(get_size(), const_cast<variant_associative_view*>(this));
	}

	std::pair<variant_associative_view::iterator, variant_associative_view::iterator> variant_associative_view::equal_range(argument key) const REFLECTPP_NOEXCEPT
	{
		////////////////////////////////////////////////////////////////////////////////////
		return std::pair<variant_associative_view::iterator, variant_associative_view::iterator>();
	}

	void variant_associative_view::erase(argument key) REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return;

		m_data.m_type->m_associative_erase(m_data.m_value, key.get_raw_data());
	}

	variant_associative_view::iterator find(argument key) REFLECTPP_NOEXCEPT
	{
		////////////////////////////////////////////////////////////////////////////////////
	}

	type variant_associative_view::get_key_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_key_type) : type();
	}

	size_t variant_associative_view::get_size() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_associative_size(m_data.m_value) : 0;
	}

	type variant_associative_view::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	type variant_associative_view::get_value_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_value_type) : type();
	}

	/*variant_associative_view::iterator variant_associative_view::insert(argument key) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || key.get_type() != get_key_type())
			return end();

		m_data.m_type->m_sequence_insert(m_data.m_value, pos.get_index(), value.get_raw_data());
		return begin() + pos.get_index();
	}*/

	void variant_associative_view::insert(argument key, argument value) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || key.get_type() != get_key_type() || value.get_type() != get_value_type())
			return;

		m_data.m_type->m_associative_insert(m_data.m_value, key.get_raw_data(), value.get_raw_data());
	}

	bool variant_associative_view::is_empty() const REFLECTPP_NOEXCEPT
	{
		return get_size() == 0;
	}

	bool variant_associative_view::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}
}
