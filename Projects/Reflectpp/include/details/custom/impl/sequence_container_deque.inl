// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto sequence_container<std::deque<T>>::get_data() REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::deque<T>;
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

			data.m_clear = [](class_type* container)
			{
				container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_erase = [](class_type* container, iterator pos) -> iterator
			{
				return container->erase(pos);
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				return container->insert(pos, value);
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}
	}
}
