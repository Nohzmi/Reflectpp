// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE variant::~variant()
	{
		clear();
	}

	REFLECTPP_INLINE variant::variant(const variant& copy)
	{
		*this = copy;
	}

	REFLECTPP_INLINE variant& variant::operator=(const variant& copy)
	{
		m_data.m_is_owner = copy.is_valid();
		m_data.m_type = copy.m_data.m_type;
		m_data.m_value = copy.is_valid() ? m_data.m_type->m_factory->m_copy(copy.m_data.m_value) : nullptr;
		return *this;
	}

	REFLECTPP_INLINE variant::variant(const details::variant_data& data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE variant::variant(T&& object) REFLECTPP_NOEXCEPT
	{
		m_data.m_is_owner = !std::is_reference_v<T>;
		m_data.m_type = details::registry::get_instance().get_type(object);

		if constexpr (std::is_reference_v<T>)
		{
			m_data.m_value = &object;
		}
		else
		{
			m_data.m_value = new T(std::forward<T>(object));
		}
	}

	REFLECTPP_INLINE variant::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	void variant::clear() REFLECTPP_NOEXCEPT
	{
		if (m_data.m_is_owner && is_valid())
		{
			m_data.m_type->m_factory->m_destructor(m_data.m_value);
			m_data.m_value = nullptr;
		}

		m_data = details::variant_data();
	}

	template<typename T>
	REFLECTPP_INLINE T& variant::get_value() REFLECTPP_NOEXCEPT
	{
		return *static_cast<T*>(m_data.m_value);
	}

	template<typename T>
	REFLECTPP_INLINE const T& variant::get_value() const REFLECTPP_NOEXCEPT
	{
		return *static_cast<T*>(m_data.m_value);
	}

	REFLECTPP_INLINE bool variant::is_sequential_container() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data.m_type->m_is_sequence_container : false;
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::is_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? details::registry::get_instance().get_type<T>() == m_data.m_type : false;
	}

	REFLECTPP_INLINE bool variant::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data.m_value != nullptr && m_data.m_type != nullptr;
	}
}
