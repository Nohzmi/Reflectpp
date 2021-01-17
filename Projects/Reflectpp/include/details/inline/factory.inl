// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE factory factory::get() REFLECTPP_NOEXCEPT
	{
		return factory(details::registry::get_instance().get_factory<T>());
	}
}
