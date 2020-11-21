// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return T::type_id();
		}

		template<typename T>
		REFLECTPP_INLINE size_t type_id(T* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return object->get_type_id();
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return T::type_name();
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name(T* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return object->get_type_name();
		}
	}
}
