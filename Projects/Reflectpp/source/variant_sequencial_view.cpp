// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant_sequencial_view.h"

#include "details/sequence_type.h"
#include "details/sequence_function.h"
#include "argument.h"
#include "factory.h"
#include "variant.h"

namespace reflectpp
{
	bool variant_sequencial_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index == rhs.m_index) && (m_variant_sequencial_view == rhs.m_variant_sequencial_view);
	}

	bool variant_sequencial_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index != rhs.m_index) || (m_variant_sequencial_view != rhs.m_variant_sequencial_view);
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator++(int) REFLECTPP_NOEXCEPT
	{
		variant_sequencial_view::iterator it(*this);
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
		variant_sequencial_view::iterator it(*this);
		--(*this);
		return it;
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator+=(int i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator+(int i) REFLECTPP_NOEXCEPT
	{
		variant_sequencial_view::iterator it(*this);
		it += i;
		return it;
	}

	variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator-=(int i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	variant_sequencial_view::iterator variant_sequencial_view::iterator::operator-(int i) REFLECTPP_NOEXCEPT
	{
		variant_sequencial_view::iterator it(*this);
		it -= i;
		return it;
	}

	variant variant_sequencial_view::iterator::operator*() const REFLECTPP_NOEXCEPT
	{
		return m_variant_sequencial_view->get_value(m_index);
	}

	variant variant_sequencial_view::iterator::get_data() const REFLECTPP_NOEXCEPT
	{
		return *(*this);
	}

	variant_sequencial_view::~variant_sequencial_view()
	{
		if (m_is_owner && m_data != nullptr)
		{
			m_sequence_type->get_factory().destroy(m_data);
			m_data = nullptr;
		}
	}

	variant_sequencial_view::variant_sequencial_view(const variant_sequencial_view& copy) :
		m_data{ copy.m_sequence_type->get_factory().copy(copy.m_data) },
		m_is_owner{ true },
		m_sequence_type{ copy.m_sequence_type }
	{
	}

	variant_sequencial_view& variant_sequencial_view::operator=(const variant_sequencial_view& copy)
	{
		m_data = copy.m_sequence_type->get_factory().copy(copy.m_data);
		m_is_owner = true;
		m_sequence_type = copy.m_sequence_type;

		return *this;
	}

	variant_sequencial_view::operator bool() const
	{
		return is_valid();
	}

	variant_sequencial_view::iterator variant_sequencial_view::begin() const
	{
		iterator it;
		it.m_index = 0;
		it.m_variant_sequencial_view = this;

		return it;
	}

	void variant_sequencial_view::clear()
	{
		m_sequence_type->get_sequence_function()->clear(m_data);
	}

	variant_sequencial_view::iterator variant_sequencial_view::end() const
	{
		iterator it;
		it.m_index = get_size();
		it.m_variant_sequencial_view = this;

		return it;
	}

	variant_sequencial_view::iterator variant_sequencial_view::erase(const iterator& pos)
	{
		m_sequence_type->get_sequence_function()->erase(m_data, pos.m_index);
		return begin() + pos.m_index;
	}

	size_t variant_sequencial_view::get_size() const
	{
		return m_sequence_type->get_sequence_function()->size(m_data);;
	}

	type& variant_sequencial_view::get_type() const
	{
		return *m_sequence_type;
	}

	variant variant_sequencial_view::get_value(size_t index) const
	{
		void* value{ m_sequence_type->get_sequence_function()->get(m_data, index) };
		return variant(value, false, m_sequence_type->get_data_type());
	}

	type& variant_sequencial_view::get_value_type() const
	{
		return *m_sequence_type->get_data_type();
	}

	variant_sequencial_view::iterator variant_sequencial_view::insert(const iterator& pos, const argument& value) const
	{
		REFLECTPP_ASSERT(value.m_var->m_type == m_sequence_type->get_data_type(), "invalid value type");
		m_sequence_type->get_sequence_function()->insert(m_data, pos.m_index, value.m_var->m_data);
		return begin() + pos.m_index;
	}

	bool variant_sequencial_view::is_empty() const
	{
		return get_size() == 0;
	}

	bool variant_sequencial_view::is_valid() const
	{
		return m_data != nullptr;
	}

	void variant_sequencial_view::set_size(size_t size) const
	{
		m_sequence_type->get_sequence_function()->resize(m_data, size);
	}

	void variant_sequencial_view::set_value(size_t index, const argument& value) const
	{
		REFLECTPP_ASSERT(value.m_var->m_type == m_sequence_type->get_data_type(), "invalid value type");
		m_sequence_type->get_sequence_function()->set(m_data, index, value.m_var->m_data);
	}

	variant_sequencial_view::variant_sequencial_view(void* data, bool is_owner, details::sequence_type* _sequence_type) :
		m_data{ data },
		m_is_owner{ false }, //TODO à enlever si ça marche
		m_sequence_type{ _sequence_type }
	{
	}
}
