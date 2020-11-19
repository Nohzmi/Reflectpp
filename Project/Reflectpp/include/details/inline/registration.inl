// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	inline registration registration::base() noexcept
	{
		details::registry::get_instance().add_base<T>(m_type);
		return *this;
	}

	template<typename T>
	inline registration registration::class_() noexcept
	{
		return registration(details::registry::get_instance().add_type<T>());
	}

	template<typename T, typename PropertyT>
	inline registration registration::property(const char* name, PropertyT T::* addr) noexcept
	{
		details::registry::get_instance().add_property(m_type, name, addr);
		return *this;
	}

	template<typename T, typename PropertyT>
	inline registration registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept
	{
		details::registry::get_instance().add_property(m_type, name, getter, setter);
		return *this;
	}
}
