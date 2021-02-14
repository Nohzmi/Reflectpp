// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename Class>
		REFLECTPP_INLINE auto wrapper_get() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> std::pair<type_data*, void*>
			{
				auto value{ wrapper<Class>::get_data().m_get(static_cast<Class*>(container)) };
				return std::make_pair(registry::get_instance().get_type(value), static_cast<void*>(value));
			};
		}

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto wrapper_reset() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* ptr)
			{
				wrapper<Class>::get_data().m_reset(static_cast<Class*>(container), static_cast<Value*>(ptr));
			};
		}
	}
}
