// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::forward_list<T>) REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::forward_list<T>;
			using iterator = typename class_type::iterator;
			using value_type = typename class_type::value_type;

			sequence_container_data<class_type, iterator, value_type> data;

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
				for (auto it = container->before_begin(); it != container->end(); ++it)
				{
					auto next = it;

					if (++next == pos)
						return container->erase_after(it);
				}

				return container->end();
			};

			data.m_insert = [](class_type* container, iterator pos, const value_type& value) -> iterator
			{
				for (auto it = container->before_begin(); it != container->end(); ++it)
				{
					auto next = it;

					if (++next == pos)
						return container->insert_after(it, value);
				}

				return container->end();
			};

			data.m_resize = [](class_type* container, size_t count)
			{
				container->resize(count);
			};

			return data;
		}
	}
}
