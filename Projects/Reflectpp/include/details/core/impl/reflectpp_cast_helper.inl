// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T, typename U>
		REFLECTPP_INLINE std::remove_pointer_t<T>* cast(U* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (!std::is_pointer_v<T>)
			{
				static_assert(false, "try to cast to a non pointer type");
				return nullptr;
			}
			else if constexpr (!is_valid_type<std::remove_pointer_t<T>>::value)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else if constexpr (!is_valid_type<U>::value)
			{
				REFLECTPP_LOG("invalid object type");
				return nullptr;
			}
			else
			{
				bool can_cast{ can_cast(get_type(object), registry::get_instance().get_type<std::remove_pointer_t<T>>()) };
				return can_cast ? reinterpret_cast<T>(object) : nullptr;
			}
		}
	}
}
