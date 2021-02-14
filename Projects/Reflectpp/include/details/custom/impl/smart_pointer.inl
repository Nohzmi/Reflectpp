// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto smart_pointer<T>::get_data() REFLECTPP_NOEXCEPT
		{
			return smart_pointer_data<void, void>();
		}
	}
}
