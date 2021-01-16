// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE bool variant_sequencial_view::iterator::operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index == rhs.m_index) && (m_variant_sequencial_view == rhs.m_variant_sequencial_view);
	}

	REFLECTPP_INLINE bool variant_sequencial_view::iterator::operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index != rhs.m_index) || (m_variant_sequencial_view != rhs.m_variant_sequencial_view);
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::iterator::operator++(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		++(*this);
		return it;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator--() REFLECTPP_NOEXCEPT
	{
		--m_index;
		return *this;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::iterator::operator--(int) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		--(*this);
		return it;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator+=(int i) REFLECTPP_NOEXCEPT
	{
		m_index += i;
		return *this;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::iterator::operator+(int i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it += i;
		return it;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator& variant_sequencial_view::iterator::operator-=(int i) REFLECTPP_NOEXCEPT
	{
		m_index -= i;
		return *this;
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::iterator::operator-(int i) REFLECTPP_NOEXCEPT
	{
		auto it(*this);
		it -= i;
		return it;
	}

	REFLECTPP_INLINE variant_sequencial_view::~variant_sequencial_view()
	{
		if (m_data.m_is_owner && is_valid())
		{
			m_data.m_type->m_factory->m_destructor(m_data.m_value);
			m_data.m_value = nullptr;
		}
	}

	REFLECTPP_INLINE variant_sequencial_view::variant_sequencial_view(const variant_sequencial_view& copy)
	{
		*this = copy;
	}

	REFLECTPP_INLINE variant_sequencial_view& variant_sequencial_view::operator=(const variant_sequencial_view& copy)
	{
		m_data.m_is_owner = copy.is_valid();
		m_data.m_type = copy.m_data.m_type;
		m_data.m_value = copy.is_valid() ? m_data.m_type->m_factory->m_copy(copy.m_data.m_value) : nullptr;
		return *this;
	}

	REFLECTPP_INLINE variant_sequencial_view::variant_sequencial_view(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	REFLECTPP_INLINE variant_sequencial_view::operator bool() const
	{
		return is_valid();
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::begin() const
	{
		return iterator(0, const_cast<variant_sequencial_view*>(this));
	}

	REFLECTPP_INLINE void variant_sequencial_view::clear()
	{
		if (is_valid())
			m_data.m_type->m_sequence_clear(m_data.m_value);
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::end() const
	{
		return iterator(get_size(), const_cast<variant_sequencial_view*>(this));
	}

	REFLECTPP_INLINE variant_sequencial_view::iterator variant_sequencial_view::erase(const iterator& pos)
	{
		if (!is_valid() || pos.m_index >= get_size())
			return end();

		m_data.m_type->m_sequence_erase(m_data.m_value, pos.m_index);
		return begin() + pos.m_index;
	}

	REFLECTPP_INLINE size_t variant_sequencial_view::get_size() const
	{
		return is_valid() ? m_data.m_type->m_sequence_size(m_data.m_value) : 0;
	}

	REFLECTPP_INLINE bool variant_sequencial_view::is_empty() const
	{
		return get_size() == 0;
	}

	REFLECTPP_INLINE bool variant_sequencial_view::is_valid() const
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}

	REFLECTPP_INLINE void variant_sequencial_view::set_size(size_t size) const
	{
		if (is_valid())
			m_data.m_type->m_sequence_resize(m_data.m_value, size);
	}
}
