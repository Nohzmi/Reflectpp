// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto sequence_container<T>::get_data() REFLECTPP_NOEXCEPT
		{
			return sequence_container_data();
		}
	}
}
