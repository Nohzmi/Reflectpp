// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT
		{
			if constexpr (has_registered<decay<T>>::value)
			{
				return decay<T>::type_id();
			}
			else
			{
				return typeid(decay<T>).hash_code();
			}
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT
		{
			if constexpr (has_registered<decay<T>>::value)
			{
				return decay<T>::type_name();
			}
			else
			{
				return typeid(decay<T>).name();
			}
		}
	}
}
