// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE registration::registration(details::type_data* type) REFLECTPP_NOEXCEPT :
		m_type{ type }
	{
	}

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
		details::registry::get_instance().add_property(m_type, name, addr, specifiers);
		return *this;
	}

	template<typename T, typename PropertyT>
	REFLECTPP_INLINE registration registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers) REFLECTPP_NOEXCEPT
	{
		details::registry::get_instance().add_property(m_type, name, getter, setter, specifiers);
		return *this;
	}
}
