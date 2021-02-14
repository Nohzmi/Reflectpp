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
				auto obj{ static_cast<Class*>(container) };
				auto value{ get_smart_pointer_data(obj).m_get(obj) };
				return std::make_pair(registry::get_instance().get_type(value), static_cast<void*>(value));
			};
		}
	}
}
