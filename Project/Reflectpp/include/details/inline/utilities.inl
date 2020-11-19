// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		inline size_t type_id() noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return T::type_id();
		}

		template<typename T>
		inline size_t type_id(T* object) noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return object->get_type_id();
		}

		template<typename T>
		inline const char* type_name() noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return T::type_name();
		}

		template<typename T>
		inline const char* type_name(T* object) noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return object->get_type_name();
		}
	}
}
