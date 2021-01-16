// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_variant{ var }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE instance::instance(T& object) REFLECTPP_NOEXCEPT :
		m_variant{ variant(object) }
	{
	}

	REFLECTPP_INLINE instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	REFLECTPP_INLINE bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_variant.is_valid();
	}
}
