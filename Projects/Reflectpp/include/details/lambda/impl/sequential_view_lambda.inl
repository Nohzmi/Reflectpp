// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_assign() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index, void* value)
			{
				auto obj{ static_cast<Class*>(container) };
				get_sequence_container_data(*obj).m_at(obj, index) = *static_cast<Value*>(value);
			};
		}

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_assign_impl() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index, void* value)
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ get_sequence_container_data(*obj) };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						*it = *static_cast<Value*>(value);
						break;
					}
				}
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_at() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index) -> void*
			{
				auto obj{ static_cast<Class*>(container) };
				return static_cast<void*>(&get_sequence_container_data(*obj).m_at(obj, index));
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_at_impl() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index) -> void*
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ get_sequence_container_data(*obj) };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
					if (i == index)
						return static_cast<void*>(&(*it));

				return nullptr;
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_clear() REFLECTPP_NOEXCEPT
		{
			return [](void* container)
			{
				auto obj{ static_cast<Class*>(container) };
				get_sequence_container_data(*obj).m_clear(obj);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_erase() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index)
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ get_sequence_container_data(*obj) };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						data.m_erase(obj, it);
						break;
					}
				}
			};
		}

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_insert() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index, void* value)
			{
				auto obj{ static_cast<Class*>(container) };
				auto val{ static_cast<Value*>(value) };
				auto data{ get_sequence_container_data(*obj) };

				bool has_insert{ false };
				size_t i{ 0 };

				for (auto it = data.m_begin(obj); it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						data.m_insert(obj, it, *val);
						has_insert = true;
						break;
					}
				}

				if (!has_insert && i == index)
					data.m_insert(obj, data.m_end(obj), *val);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_resize() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t size)
			{
				auto obj{ static_cast<Class*>(container) };
				get_sequence_container_data(*obj).m_resize(obj, size);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_size() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> size_t
			{
				auto obj{ static_cast<Class*>(container) };
				return get_sequence_container_data(*obj).m_size(obj);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_size_impl() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> size_t
			{
				size_t size{ 0 };

				for (auto& it : *static_cast<Class*>(container))
				{
					(void)it;
					++size;
				}

				return size;
			};
		}
	}
}
