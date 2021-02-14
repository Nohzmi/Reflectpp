// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename>
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

	template<typename T>
	REFLECTPP_INLINE bool variant::can_convert() const REFLECTPP_NOEXCEPT
	{
		return can_convert(type(details::registry::get_instance().get_type<std::remove_pointer_t<T>>()));
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::convert() REFLECTPP_NOEXCEPT
	{
		return convert(type(details::registry::get_instance().get_type<std::remove_pointer_t<T>>()));
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

	template<typename T>
	REFLECTPP_INLINE bool variant::is_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? details::registry::get_instance().get_type<T>() == m_data.m_type : false;
	}
}
