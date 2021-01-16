// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE property::property(details::property_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	REFLECTPP_INLINE bool property::operator==(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data == rhs.m_data;
	}

	REFLECTPP_INLINE bool property::operator!=(const property& rhs) const REFLECTPP_NOEXCEPT
	{
		return m_data != rhs.m_data;
	}

	REFLECTPP_INLINE property::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	REFLECTPP_INLINE size_t property::get_id() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_id : 0;
	}

	REFLECTPP_INLINE const char* property::get_name() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_name : "";
	}

	REFLECTPP_INLINE size_t property::get_specifiers() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_specifiers : 0;
	}

	REFLECTPP_INLINE bool property::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}
}
