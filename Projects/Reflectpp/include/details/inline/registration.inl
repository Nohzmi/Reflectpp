// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE registration registration::base() REFLECTPP_NOEXCEPT
	{
		if (m_type != nullptr)
			details::registry::get_instance().add_base<T>(m_type);

		return *this;
	}

	template<typename T>
	REFLECTPP_INLINE registration registration::class_() REFLECTPP_NOEXCEPT
	{
		return registration(details::registry::get_instance().add_type<T>());
	}

	template<typename T>
	REFLECTPP_INLINE registration registration::enumeration(const char* name) REFLECTPP_NOEXCEPT
	{
		return registration(details::registry::get_instance().add_enumeration<T>(name));
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT
	{
		if (m_type != nullptr)
			details::registry::get_instance().add_property(m_type, name, addr, specifiers);

		return *this;
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers) REFLECTPP_NOEXCEPT
	{
		if (m_type != nullptr)
			details::registry::get_instance().add_property(m_type, name, getter, setter, specifiers);

		return *this;
	}

	template<typename EnumT>
	REFLECTPP_INLINE registration registration::value(const char* name, EnumT value) REFLECTPP_NOEXCEPT
	{
		if (m_type != nullptr)
			details::registry::get_instance().add_value(m_type, name, value);

		return *this;
	}
}
