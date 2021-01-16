// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE type_info::type_info(details::type_info_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	REFLECTPP_INLINE bool type_info::operator==(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data == rhs.m_data;
	}

	REFLECTPP_INLINE bool type_info::operator!=(const type_info& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data != rhs.m_data;
	}

	REFLECTPP_INLINE type_info::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	template<typename T>
	REFLECTPP_INLINE type_info type_info::get() REFLECTPP_NOEXCEPT
	{
		return type_info(details::registry::get_instance().get_type_info<T>());
	}

	REFLECTPP_INLINE size_t type_info::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_id : 0;
	}

	REFLECTPP_INLINE const char* type_info::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_name : "";
	}

	REFLECTPP_INLINE bool type_info::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}
}
