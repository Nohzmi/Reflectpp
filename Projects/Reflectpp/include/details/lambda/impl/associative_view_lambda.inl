// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_at() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index) -> std::pair<void*, void*>
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ associative_container<Class>::get_data() };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						if constexpr (has_value_type<Class>::value)
						{
							return std::make_pair(static_cast<void*>(const_cast<Key*>(&(it->first))), static_cast<void*>(&(it->second)));
						}
						else
						{
							return std::make_pair(static_cast<void*>(const_cast<Key*>(&(*it))), nullptr);
						}
					}
				}

				return std::make_pair(nullptr, nullptr);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto associative_view_clear() REFLECTPP_NOEXCEPT
		{
			return [](void* container)
			{
				associative_container<Class>::get_data().m_clear(static_cast<Class*>(container));
			};
		}

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_equal_range() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* key)->std::pair<size_t, size_t>
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ associative_container<Class>::get_data() };
				auto range{ data.m_equal_range(obj, *static_cast<Key*>(key)) };

				if (range.first == range.second)
				{
					if (range.first == data.m_begin(obj))
					{
						return std::make_pair(0, 0);
					}
					else if (range.first == data.m_end(obj))
					{
						size_t size{ data.m_size(obj) };
						return std::make_pair(size, size);
					}
				}

				std::pair<size_t, size_t> size_range{ 0, 0 };
				std::pair<bool, bool> stop{ false, false };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
				{
					if (it == range.first)
					{
						size_range.first = i;
						stop.first = true;
					}
					else if (it == range.second)
					{
						size_range.second = i;
						stop.second = true;
					}

					if (stop.first && stop.second)
						break;
				}

				return size_range;
			};
		}

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_erase() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* key) -> size_t
			{
				return associative_container<Class>::get_data().m_erase(static_cast<Class*>(container), *static_cast<Key*>(key));
			};
		}

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_find() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* key) -> size_t
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ associative_container<Class>::get_data() };
				auto find{ data.m_find(obj, *static_cast<Key*>(key)) };

				if (find == data.m_begin(obj))
					return data.m_size(obj);

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
					if (it == find)
						return i;

				return data.m_size(obj);
			};
		}

		template<typename Class, typename Iterator, typename Key, typename Value>
		REFLECTPP_INLINE auto associative_view_insert() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* key, void* value) -> std::pair<size_t, bool>
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ associative_container<Class>::get_data() };
				auto insert{ data.m_insert(obj, *static_cast<Key*>(key), value != nullptr ? *static_cast<Value*>(value) : Value()) };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
					if (it == insert.first)
						return std::make_pair(i, insert.second);

				return std::make_pair(data.m_size(obj), false);
			};
		}

		template<typename Class, typename Iterator, typename Key>
		REFLECTPP_INLINE auto associative_view_insert() REFLECTPP_NOEXCEPT
		{
			return [](void* container, void* key, void*) -> std::pair<size_t, bool>
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ associative_container<Class>::get_data() };
				auto insert{ data.m_insert(obj, *static_cast<Key*>(key)) };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
					if (it == insert.first)
						return std::make_pair(i, insert.second);

				return std::make_pair(data.m_size(obj), false);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto associative_view_size() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> size_t
			{
				return associative_container<Class>::get_data().m_size(static_cast<Class*>(container));
			};
		}
	}
}
