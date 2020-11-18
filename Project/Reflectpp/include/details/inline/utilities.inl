// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cassert>
#include <cstdio>
#include <typeinfo>

namespace reflectpp
{
	namespace details
	{
		template<class ...Args>
		void _assert(bool expr, const char* format, Args ...args) noexcept
		{
			if (!expr)
			{
				printf(format, args...);
				assert(false);
			}
		}

		template<typename T>
		size_t type_id() noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return T::type_id();
		}

		template<typename T>
		size_t type_id(T* object) noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).hash_code();
			else
				return object->get_type_id();
		}

		template<typename T>
		const char* type_name() noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return T::type_name();
		}

		template<typename T>
		const char* type_name(T* object) noexcept
		{
			if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
				return typeid(T).name();
			else
				return object->get_type_name();
		}
	}
}
