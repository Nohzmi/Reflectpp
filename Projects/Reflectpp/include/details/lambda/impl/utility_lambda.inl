// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto utility_compare() REFLECTPP_NOEXCEPT
		{
			return [](void* lhs, void* rhs) -> bool
			{
				if constexpr (has_operator_equal<T>::value || is_std_container<T>::value || is_enum_type<T>::value)
				{
					return *static_cast<T*>(lhs) == *static_cast<T*>(rhs);
				}
				else
				{
					return false;
				}
			};
		}

		template<typename From, typename To>
		REFLECTPP_INLINE auto utility_convert() REFLECTPP_NOEXCEPT
		{
			return [](void* object) -> void*
			{
				if constexpr (std::is_convertible_v<From, To> || is_enum_type<From>::value || is_enum_type<To>::value)
				{
#pragma warning(push)
#pragma warning(disable: 4244)

					return new To(static_cast<To>(*static_cast<From*>(object)));

#pragma warning (pop)
				}
				else
				{
					return nullptr;
				}
			};
		}
	}
}
