// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_constructor() REFLECTPP_NOEXCEPT
		{
			return []() -> void*
			{
				if constexpr (std::is_constructible_v<T>)
				{
					return new T();
				}
				else
				{
					return nullptr;
				}
			};
		}

		template<typename T>
		REFLECTPP_INLINE auto get_copy_constructor() REFLECTPP_NOEXCEPT
		{
			return [](void* object) -> void*
			{
				if constexpr (std::is_copy_constructible_v<T>)
				{
					return new T(*static_cast<T*>(object));
				}
				else
				{
					return nullptr;
				}
			};
		}

		template<typename T>
		REFLECTPP_INLINE auto get_destructor() REFLECTPP_NOEXCEPT
		{
			return [](void* object)
			{
				if constexpr (std::is_destructible_v<T>)
					delete static_cast<T*>(object);
			};
		}
	}
}
