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
				if constexpr (std::is_copy_constructible_v<Value> || std::is_copy_assignable_v<Value>) // TODO
				{
					sequence_container<Class>::get_data().m_at(static_cast<Class*>(container), index) = *static_cast<Value*>(value);
				}
				else
				{
					sequence_container<Class>::get_data().m_at(static_cast<Class*>(container), index) = std::move(*static_cast<Value*>(value));
				}
			};
		}

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_assign_impl() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index, void* value)
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ sequence_container<Class>::get_data() };

				for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						if constexpr (std::is_copy_constructible_v<Value> || std::is_copy_assignable_v<Value>) // TODO
						{
							*it = *static_cast<Value*>(value);
						}
						else
						{
							*it = std::move(*static_cast<Value*>(value));
						}
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
				return static_cast<void*>(&sequence_container<Class>::get_data().m_at(static_cast<Class*>(container), index));
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_at_impl() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index) -> void*
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ sequence_container<Class>::get_data() };

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
				sequence_container<Class>::get_data().m_clear(static_cast<Class*>(container));
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_erase() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t index)
			{
				auto obj{ static_cast<Class*>(container) };
				auto data{ sequence_container<Class>::get_data() };

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
				auto data{ sequence_container<Class>::get_data() };

				bool has_insert{ false };
				size_t i{ 0 };

				for (auto it = data.m_begin(obj); it != data.m_end(obj); ++it, ++i)
				{
					if (i == index)
					{
						data.m_insert(obj, it, std::move(*val)); // TODO
						has_insert = true;
						break;
					}
				}

				if (!has_insert && i == index)
					data.m_insert(obj, data.m_end(obj), std::move(*val)); // TODO
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_resize() REFLECTPP_NOEXCEPT
		{
			return [](void* container, size_t size)
			{
				sequence_container<Class>::get_data().m_resize(static_cast<Class*>(container), size);
			};
		}

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_size() REFLECTPP_NOEXCEPT
		{
			return [](void* container) -> size_t
			{
				return sequence_container<Class>::get_data().m_size(static_cast<Class*>(container));
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
