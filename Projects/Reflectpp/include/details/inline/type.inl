// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE type::type(details::type_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	REFLECTPP_INLINE bool type::operator==(const type& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data == rhs.m_data;
	}

	REFLECTPP_INLINE bool type::operator!=(const type& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data != rhs.m_data;
	}

	REFLECTPP_INLINE type::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	template<typename T, typename U>
	REFLECTPP_INLINE T type::cast(U* object) REFLECTPP_NOEXCEPT
	{
		return details::registry::get_instance().cast<T>(object);
	}

	template<typename T>
	REFLECTPP_INLINE type type::get() REFLECTPP_NOEXCEPT
	{
		return *details::registry::get_instance().get_type<T>();
	}

	template<typename T>
	REFLECTPP_INLINE type type::get(T&& object) REFLECTPP_NOEXCEPT
	{
		return *details::registry::get_instance().get_type(std::forward<T>(object));
	}

	REFLECTPP_INLINE size_t type::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_type_info->m_id : 0;
	}

	REFLECTPP_INLINE const char* type::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_type_info->m_name : "";
	}

	REFLECTPP_INLINE size_t type::get_sizeof() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_size : 0;
	}

	REFLECTPP_INLINE bool type::is_sequential_container() const REFLECTPP_NOEXCEPT
	{
		return m_data->m_is_sequence_container;
	}

	REFLECTPP_INLINE bool type::is_valid() const REFLECTPP_NOEXCEPT
	{
		return false;
	}
}
