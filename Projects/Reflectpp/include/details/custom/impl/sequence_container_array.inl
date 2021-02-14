// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T, size_t Size>
		REFLECTPP_INLINE auto sequence_container<std::array<T, Size>>::get_data() REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::array<T, Size>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

			data.m_at = [](class_type* container, size_t pos) -> value_type&
			{
				return container->at(pos);
			};

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}
	}
}
