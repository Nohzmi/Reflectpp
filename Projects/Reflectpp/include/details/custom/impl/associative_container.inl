// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto associative_container<T>::get_data() REFLECTPP_NOEXCEPT
		{
			return associative_container_data();
		}
	}
}
