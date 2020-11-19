// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	inline variant::variant(T* object) noexcept :
		m_data{ object },
		m_is_owner{ false },
		m_type{ details::registry::get_instance().get_type(object) }
	{
	}

	template<typename T>
	inline T& variant::get_value() noexcept
	{
		REFLECTPP_ASSERT(is_valid(), "variant::get_value<%s>() : invalid variant\n", details::type_name<T>());
		REFLECTPP_ASSERT(details::registry::get_instance().get_type<T>() == m_type, "variant::get_value<%s>() : wrong type, stored value is a %s\n", details::type_name<T>(), details::registry::get_instance().get_type_name(m_type));

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	inline const T& variant::get_value() const noexcept
	{
		REFLECTPP_ASSERT(is_valid(), "variant::get_value<%s>() : invalid variant\n", details::type_name<T>());
		REFLECTPP_ASSERT(details::registry::get_instance().get_type<T>() == m_type, "variant::get_value<%s>() : wrong type, stored value is a %s\n", details::type_name<T>(), details::registry::get_instance().get_type_name(m_type));

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	inline bool variant::is_type() const noexcept
	{
		return is_valid() ? details::registry::get_instance().get_type<T>() == m_type : false;
	}
}
