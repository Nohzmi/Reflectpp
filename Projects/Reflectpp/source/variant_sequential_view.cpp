// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_sequential_view.h"

#include "argument.h"
#include "type.h"

namespace reflectpp
{
	variant_sequential_view::iterator::iterator(size_t index, variant_sequential_view* variant) REFLECTPP_NOEXCEPT :
		m_index{ index },
		m_variant{ variant }
	{
	}

	variant variant_sequential_view::iterator::get_data() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->get_value(m_index) : variant();
	}

	bool variant_sequential_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	variant variant_sequential_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		return get_data();
	}

	variant_sequential_view::iterator variant_sequential_view::iterator::operator+(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it += i;
		return it;
	}

	variant_sequential_view::iterator& variant_sequential_view::iterator::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	variant_sequential_view::iterator variant_sequential_view::iterator::operator++(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		++(*this);
		return it;
	}

	variant_sequential_view::iterator& variant_sequential_view::iterator::operator+=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	variant_sequential_view::iterator variant_sequential_view::iterator::operator-(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it -= i;
		return it;
	}

	variant_sequential_view::iterator& variant_sequential_view::iterator::operator--() REFLECTPP_NOEXCEPT
	{
		--m_index;
		return *this;
	}

	variant_sequential_view::iterator variant_sequential_view::iterator::operator--(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		--(*this);
		return it;
	}

	variant_sequential_view::iterator& variant_sequential_view::iterator::operator-=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	bool variant_sequential_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_index == rhs.m_index && m_variant == rhs.m_variant;
	}

	variant_sequential_view::variant_sequential_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	variant_sequential_view::iterator variant_sequential_view::begin() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return iterator();

		return iterator(0, const_cast<variant_sequential_view*>(this));
	}

	void variant_sequential_view::clear() REFLECTPP_NOEXCEPT
	{
		if (is_valid() && m_data.m_type->m_sequential_view->m_clear != nullptr)
			m_data.m_type->m_sequential_view->m_clear(m_data.m_value);
	}

	variant_sequential_view::iterator variant_sequential_view::end() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return iterator();

		return iterator(get_size(), const_cast<variant_sequential_view*>(this));
	}

	variant_sequential_view::iterator variant_sequential_view::erase(const iterator& pos) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_erase == nullptr || pos.m_index >= get_size())
			return iterator();

		m_data.m_type->m_sequential_view->m_erase(m_data.m_value, pos.m_index);
		return iterator(pos.m_index, this);
	}

	size_t variant_sequential_view::get_size() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_size == nullptr)
			return 0;

		return m_data.m_type->m_sequential_view->m_size(m_data.m_value);
	}

	type variant_sequential_view::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	variant variant_sequential_view::get_value(size_t index) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_at == nullptr || index >= get_size())
			return variant();

		void* value{ m_data.m_type->m_sequential_view->m_at(m_data.m_value, index) };
		return variant({ false, m_data.m_type->m_sequential_view->m_value_type, value });
	}

	type variant_sequential_view::get_value_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_sequential_view->m_value_type) : type();
	}

	variant_sequential_view::iterator variant_sequential_view::insert(const iterator& pos, argument value) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_insert == nullptr || pos.m_index >= get_size() + 1)
			return iterator();

		auto value_var{ static_cast<variant*>(value) };

		if (value_var == nullptr || !value_var->is_valid() || !value_var->convert(get_value_type()))
			return iterator();

		void* value_ptr{ static_cast<details::variant_data*>(*value_var)->m_value };
		m_data.m_type->m_sequential_view->m_insert(m_data.m_value, pos.m_index, value_ptr);
		return iterator(pos.m_index, this);
	}

	bool variant_sequential_view::is_dynamic() const REFLECTPP_NOEXCEPT
	{
		return is_valid() && (m_data.m_type->m_sequential_view->m_clear != nullptr || m_data.m_type->m_sequential_view->m_erase != nullptr ||
			m_data.m_type->m_sequential_view->m_insert != nullptr || m_data.m_type->m_sequential_view->m_resize != nullptr);
	}

	bool variant_sequential_view::is_empty() const REFLECTPP_NOEXCEPT
	{
		return get_size() == 0;
	}

	bool variant_sequential_view::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr && m_data.m_type->m_sequential_view != nullptr;
	}

	variant_sequential_view::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	bool variant_sequential_view::set_size(size_t size) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_resize == nullptr)
			return false;

		m_data.m_type->m_sequential_view->m_resize(m_data.m_value, size);
		return true;
	}

	bool variant_sequential_view::set_value(size_t index, argument value) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_sequential_view->m_assign == nullptr || index >= get_size())
			return false;

		auto value_var{ static_cast<variant*>(value) };

		if (value_var == nullptr || !value_var->is_valid() || !value_var->convert(get_value_type()))
			return false;

		void* value_ptr{ static_cast<details::variant_data*>(*value_var)->m_value };
		m_data.m_type->m_sequential_view->m_assign(m_data.m_value, index, value_ptr);
		return true;
	}
}
