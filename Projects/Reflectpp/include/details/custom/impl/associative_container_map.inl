// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename Key, typename T>
		REFLECTPP_INLINE auto associative_container<std::map<Key, T>>::get_data() REFLECTPP_NOEXCEPT
		{
			using class_type = typename std::map<Key, T>;
			using iterator = typename class_type::iterator;
			using key_type = typename class_type::key_type;
			using value_type = typename class_type::mapped_type;

			associative_container_data<class_type, iterator, key_type, value_type> data;

			data.m_begin = [](class_type* container) -> iterator
			{
				return container->begin();
			};

			data.m_clear = [](class_type* container)
			{
				return container->clear();
			};

			data.m_end = [](class_type* container) -> iterator
			{
				return container->end();
			};

			data.m_equal_range = [](class_type* container, const key_type& key) -> std::pair<iterator, iterator>
			{
				return container->equal_range(key);
			};

			data.m_erase = [](class_type* container, const key_type& key) -> size_t
			{
				return container->erase(key);
			};

			data.m_find = [](class_type* container, const key_type& key) -> iterator
			{
				return container->find(key);
			};

			data.m_insert = [](class_type* container, const key_type& key, const value_type& value) -> std::pair<iterator, bool>
			{
				return container->insert(std::make_pair(key, value));
			};

			data.m_size = [](class_type* container) -> size_t
			{
				return container->size();
			};

			return data;
		}
	}
}
