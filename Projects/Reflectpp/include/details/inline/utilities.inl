// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT
		{
			if constexpr (is_arithmetic<T>::value || !use_macro<T>::value)
			{
				return typeid(decay<T>).hash_code();
			}
			else
			{
				return decay<T>::type_id();
			}
		}

		template<typename T>
		REFLECTPP_INLINE size_t type_id(T&& object) REFLECTPP_NOEXCEPT
		{
			if constexpr (is_pointer_of_pointer<T>::value)
			{
				REFLECTPP_ASSERT(false, "type_name(%s&&) : unsupported type\n", typeid(T).name());
				return 0;
			}
			else if constexpr (is_same<T, type>::value)
			{
				if constexpr (is_pointer<T>::value)
				{
					return utilities::type_id(std::forward<T>(object));
				}
				else
				{
					return utilities::type_id(std::forward<T>(object));
				}
			}
			else if constexpr (is_arithmetic<T>::value || !use_macro<T>::value)
			{
				return typeid(decay<T>).hash_code();
			}
			else
			{
				if constexpr (is_pointer<T>::value)
				{
					if (std::forward<T>(object) == nullptr)
					{
						return decay<T>::type_id();
					}

					return std::forward<T>(object)->get_type_id();
				}
				else
				{
					return std::forward<T>(object).get_type_id();
				}
			}
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT
		{
			if constexpr (is_arithmetic<T>::value || !use_macro<T>::value)
			{
				return typeid(decay<T>).name();
			}
			else
			{
				return decay<T>::type_name();
			}
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name(T&& object) REFLECTPP_NOEXCEPT
		{
			if constexpr (is_pointer_of_pointer<T>::value)
			{
				REFLECTPP_ASSERT(false, "type_name(%s&&) : unsupported type\n", typeid(T).name());
				return "";
			}
			else if constexpr (is_same<T, type>::value)
			{
				if constexpr (is_pointer<T>::value)
				{
					return utilities::type_name(std::forward<T>(object));
				}
				else
				{
					return utilities::type_name(&std::forward<T>(object));
				}
			}
			else if constexpr (is_arithmetic<T>::value || !use_macro<T>::value)
			{
				return typeid(decay<T>).name();
			}
			else
			{
				if constexpr (is_pointer<T>::value)
				{
					if (std::forward<T>(object) == nullptr)
					{
						return decay<T>::type_name();
					}

					return std::forward<T>(object)->get_type_name();
				}
				else
				{
					return std::forward<T>(object).get_type_name();
				}
			}
		}
	}
}
