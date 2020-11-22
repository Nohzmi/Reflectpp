// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	REFLECTPP_INLINE T type::cast(U* object) REFLECTPP_NOEXCEPT
	{
		return details::registry::get_instance().cast<T>(object);
	}

	template<typename T>
	REFLECTPP_INLINE type& type::get() REFLECTPP_NOEXCEPT
	{
		return *details::registry::get_instance().get_type<T>();
	}

	template<typename T>
	REFLECTPP_INLINE type& type::get(T&& object) REFLECTPP_NOEXCEPT
	{
		return *details::registry::get_instance().get_type(std::forward<T>(object));
	}
}
