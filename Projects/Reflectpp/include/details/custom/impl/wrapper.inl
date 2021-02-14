// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto wrapper<T>::get_data() REFLECTPP_NOEXCEPT
		{
			return wrapper_data();
		}
	}
}
