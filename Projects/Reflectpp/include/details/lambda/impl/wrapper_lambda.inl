// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Value>
		REFLECTPP_INLINE auto wrapper_get() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> Value*
			{
				auto obj{ static_cast<Class*>(container) };
				return static_cast<void*>(get_smart_pointer_data(*obj).m_get(obj));
			};
		}
	}
}
