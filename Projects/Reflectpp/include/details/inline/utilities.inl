// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT
		{
			if constexpr (is_arithmetic<T>::value || !is_registered<T>::value)
			{
				return typeid(decay<T>).hash_code();
			}
			else
			{
				return decay<T>::type_id();
			}
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT
		{
			if constexpr (is_arithmetic<T>::value || !is_registered<T>::value)
			{
				return typeid(decay<T>).name();
			}
			else
			{
				return decay<T>::type_name();
			}
		}
	}
}
