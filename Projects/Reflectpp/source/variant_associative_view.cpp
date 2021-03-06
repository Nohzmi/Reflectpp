// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_associative_view.h"

#include "argument.h"
#include "type.h"

namespace reflectpp
{
	variant_associative_view::iterator::iterator(size_t index, variant_associative_view* variant) REFLECTPP_NOEXCEPT :
		m_index{ index },
		m_variant{ variant }
	{
	}

	variant variant_associative_view::iterator::get_key() const REFLECTPP_NOEXCEPT
	{
		return (*(*this)).first;
	}

	variant variant_associative_view::iterator::get_value() const REFLECTPP_NOEXCEPT
	{
		return (*(*this)).second;
	}

	bool variant_associative_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return !(*this == rhs);
	}

	std::pair<variant, variant> variant_associative_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		if (m_variant == nullptr)
			return std::make_pair(variant(), variant());

		return m_variant->get_value(m_index);
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator+(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it += i;
		return it;
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

	variant_associative_view::iterator& variant_associative_view::iterator::operator+=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	variant_associative_view::iterator variant_associative_view::iterator::operator-(size_t i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it -= i;
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

	variant_associative_view::iterator& variant_associative_view::iterator::operator-=(size_t i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	bool variant_associative_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_index == rhs.m_index && m_variant == rhs.m_variant;
	}

	variant_associative_view::variant_associative_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	variant_associative_view::iterator variant_associative_view::begin() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return iterator();

		return iterator(0, const_cast<variant_associative_view*>(this));
	}

	void variant_associative_view::clear() REFLECTPP_NOEXCEPT
	{
		if (is_valid() && m_data.m_type->m_associative_view->m_clear != nullptr)
			m_data.m_type->m_associative_view->m_clear(m_data.m_value);
	}

	variant_associative_view::iterator variant_associative_view::end() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return iterator();

		return iterator(get_size(), const_cast<variant_associative_view*>(this));
	}

	std::pair<variant_associative_view::iterator, variant_associative_view::iterator> variant_associative_view::equal_range(argument key) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_equal_range == nullptr)
			return std::make_pair(iterator(), iterator());

		auto key_var{ static_cast<variant*>(key) };

		if (key_var == nullptr || !key_var->is_valid() || !key_var->convert(get_key_type()))
			return std::make_pair(iterator(), iterator());

		void* key_ptr{ static_cast<details::variant_data*>(*key_var)->m_value };
		auto range{ m_data.m_type->m_associative_view->m_equal_range(m_data.m_value, key_ptr) };
		auto first{ iterator(range.first, const_cast<variant_associative_view*>(this)) };
		auto second{ iterator(range.second, const_cast<variant_associative_view*>(this)) };

		return std::make_pair(first, second);
	}

	size_t variant_associative_view::erase(argument key) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_erase == nullptr)
			return 0;

		auto key_var{ static_cast<variant*>(key) };

		if (key_var == nullptr || !key_var->is_valid() || !key_var->convert(get_key_type()))
			return 0;

		void* key_ptr{ static_cast<details::variant_data*>(*key_var)->m_value };
		return m_data.m_type->m_associative_view->m_erase(m_data.m_value, key_ptr);
	}

	variant_associative_view::iterator variant_associative_view::find(argument key) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_find == nullptr)
			return iterator();

		auto key_var{ static_cast<variant*>(key) };

		if (key_var == nullptr || !key_var->is_valid() || !key_var->convert(get_key_type()))
			return iterator();

		void* key_ptr{ static_cast<details::variant_data*>(*key_var)->m_value };
		size_t index{ m_data.m_type->m_associative_view->m_find(m_data.m_value, key_ptr) };
		return iterator(index, this);
	}

	type variant_associative_view::get_key_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_associative_view->m_key_type) : type();
	}

	size_t variant_associative_view::get_size() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_size == nullptr)
			return 0;

		return m_data.m_type->m_associative_view->m_size(m_data.m_value);
	}

	type variant_associative_view::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}

	type variant_associative_view::get_value_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type->m_associative_view->m_value_type) : type();
	}

	std::pair<variant_associative_view::iterator, bool> variant_associative_view::insert(argument key) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_insert == nullptr)
			return std::make_pair(iterator(), false);

		auto key_var{ static_cast<variant*>(key) };

		if (key_var == nullptr || !key_var->is_valid() || !key_var->convert(get_key_type()))
			return std::make_pair(iterator(), false);

		void* key_ptr{ static_cast<details::variant_data*>(*key_var)->m_value };
		auto it{ m_data.m_type->m_associative_view->m_insert(m_data.m_value, key_ptr, nullptr) };
		return std::make_pair(iterator(it.first, this), it.second);
	}

	std::pair<variant_associative_view::iterator, bool> variant_associative_view::insert(argument key, argument value) REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_insert == nullptr)
			return std::make_pair(iterator(), false);

		if (!static_cast<variant*>(value)->is_valid())
			insert(std::move(key));

		auto key_var{ static_cast<variant*>(key) };
		auto value_var{ static_cast<variant*>(value) };

		if (key_var == nullptr || !key_var->is_valid() || !key_var->convert(get_key_type()))
			return std::make_pair(iterator(), false);

		if (value_var == nullptr || !value_var->is_valid() || !value_var->convert(get_value_type()))
			return std::make_pair(iterator(), false);

		void* key_ptr{ static_cast<details::variant_data*>(*key_var)->m_value };
		void* value_ptr{ static_cast<details::variant_data*>(*value_var)->m_value };

		auto it{ m_data.m_type->m_associative_view->m_insert(m_data.m_value, key_ptr, value_ptr) };
		return std::make_pair(iterator(it.first, this), it.second);
	}

	bool variant_associative_view::is_empty() const REFLECTPP_NOEXCEPT
	{
		return get_size() == 0;
	}

	bool variant_associative_view::is_key_only_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_associative_view->m_value_type == nullptr : false;
	}

	bool variant_associative_view::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr && m_data.m_type->m_associative_view != nullptr;
	}

	std::pair<variant, variant> variant_associative_view::get_value(size_t index) const REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || m_data.m_type->m_associative_view->m_at == nullptr || index >= get_size())
			return std::make_pair(variant(), variant());

		auto at{ m_data.m_type->m_associative_view->m_at(m_data.m_value, index) };
		return std::make_pair(variant({ false, m_data.m_type->m_associative_view->m_key_type, at.first }), variant({false, m_data.m_type->m_associative_view->m_value_type, at.second}));
	}

	variant_associative_view::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}
}
