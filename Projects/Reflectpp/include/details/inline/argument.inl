// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE argument::argument(variant& var) REFLECTPP_NOEXCEPT :
		m_variant{ var }
	{
	}

	REFLECTPP_INLINE argument::argument(const variant& var) REFLECTPP_NOEXCEPT :
		m_variant{ var }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE argument::argument(T& object) REFLECTPP_NOEXCEPT :
		m_variant{ variant(object) }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE argument::argument(const T& object) REFLECTPP_NOEXCEPT :
	m_variant{ variant(object) }
	{
	}

	template<typename T>
	REFLECTPP_INLINE T& argument::get_value() const REFLECTPP_NOEXCEPT
	{
		return m_variant.get_value<T>();

	}

	template<typename T>
	REFLECTPP_INLINE bool argument::is_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant.is_type<T>();
	}
}
