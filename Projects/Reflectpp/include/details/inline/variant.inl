// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	REFLECTPP_INLINE variant::variant(T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_type{ details::registry::get_instance().get_type(object) }
	{
		if constexpr (std::is_pointer_v<std::decay_t<T>>)
			m_data = object;
		else
			m_data = &object;
	}

	template<typename T>
	REFLECTPP_INLINE T& variant::get_value() REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(is_valid(), "invalid variant");
		REFLECTPP_ASSERT(details::registry::get_instance().get_type<T>() == m_type, "wrong type");

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	REFLECTPP_INLINE const T& variant::get_value() const REFLECTPP_NOEXCEPT
	{
		REFLECTPP_ASSERT(is_valid(), "invalid variant");
		REFLECTPP_ASSERT(details::registry::get_instance().get_type<T>() == m_type, "wrong type");

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::is_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? details::registry::get_instance().get_type<T>() == m_type : false;
	}
}
