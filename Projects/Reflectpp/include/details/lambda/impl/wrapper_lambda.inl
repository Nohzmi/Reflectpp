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
				auto value{ smart_pointer<Class>::get_data().m_get(static_cast<Class*>(container)) };
				return std::make_pair(registry::get_instance().get_type(value), static_cast<void*>(value));
			};
		}
	}
}
