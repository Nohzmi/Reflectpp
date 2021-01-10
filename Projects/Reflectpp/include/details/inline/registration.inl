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
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_property(addr, name, specifiers, m_type);
		return *this;
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers) REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_property(getter, name, setter, specifiers, m_type);
		return *this;
	}
}
