// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	REFLECTPP_INLINE argument::argument(const T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_var{ new variant(object) }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE argument::argument(T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_var{ new variant(object) }
	{
	}

	template<typename T>
	REFLECTPP_INLINE T& argument::get_value() const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(m_var != nullptr && m_var->is_valid(), "invalid argument");
		return m_var->get_value();
	}

	template<typename T>
	REFLECTPP_INLINE bool argument::is_type() const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(m_var != nullptr && m_var->is_valid(), "invalid argument");
		return m_var->is_type<T>();
	}
}
