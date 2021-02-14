// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto wrapper<std::unique_ptr<T>>::get_data() REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::unique_ptr<T>;
			using value_type = typename class_type::element_type;

			wrapper_data<class_type, value_type> data;

			data.m_get = [](class_type* container) -> value_type*
			{
				return container->get();
			};

			data.m_reset = [](class_type* container, value_type* ptr)
			{
				container->reset(ptr);
			};

			return data;
		}
	}
}
