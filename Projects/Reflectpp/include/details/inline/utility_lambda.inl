// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_compare() REFLECTPP_NOEXCEPT
		{
			return [](void* lhs, void* rhs) -> bool
			{
				if constexpr (has_operator_equal<T>::value || is_std_container<T>::value)
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
		REFLECTPP_INLINE auto get_convert() REFLECTPP_NOEXCEPT
		{
			return [](void* object) -> void*
			{
				if constexpr (std::is_convertible_v<From, To>)
				{
#pragma warning(push)
#pragma warning(disable: 4244)

					return new To(*static_cast<From*>(object));

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
