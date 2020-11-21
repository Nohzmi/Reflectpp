// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	inline T type::cast(U* object) noexcept
	{
		return details::registry::get_instance().cast<T>(object);
	}

	template<typename T>
	inline type& type::get() noexcept
	{
		return *details::registry::get_instance().get_type<T>();
	}

	template<typename T>
	inline type& type::get(T* object) noexcept
	{
		return *details::registry::get_instance().get_type(object);
	}
}
