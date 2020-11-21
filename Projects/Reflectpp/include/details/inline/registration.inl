// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE registration registration::base() REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_base<T>(m_type);
		return *this;
	}

	template<typename T>
	REFLECTPP_INLINE registration registration::class_() REFLECTPP_NOEXCEPT
	{
		return registration(details::registry::get_instance().add_type<T>());
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT T::* addr) REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_property(m_type, name, addr);
		return *this;
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_property(m_type, name, getter, setter);
		return *this;
	}
}
