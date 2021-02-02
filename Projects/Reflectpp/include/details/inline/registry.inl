// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE void registry::add_base(type_data* type) REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || std::is_arithmetic_v<T>)
			{
				REFLECTPP_LOG("invalid type");
			}
			else
			{
				add_base_impl(type, get_type_impl<T>());
			}
		}

		template<typename T, typename propertyT>
		REFLECTPP_INLINE void registry::add_property(type_data* type, const char* name, propertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_pointer_v<propertyT>)
			{
				REFLECTPP_LOG("pointer not supported");
			}
			else
			{
				if (get_type<T>() != type)
				{
					REFLECTPP_LOG("%s isn't in type", name);
					return;
				}

				size_t offset = (size_t)(char*)&((T*)nullptr->*addr);

				auto getter = [offset](void* object, bool& is_owner) -> void*
				{
					is_owner = false;
					return static_cast<char*>(object) + offset;
				};

				auto setter = [offset](void* object, void* value)
				{
					auto& set = *reinterpret_cast<decay<propertyT>*>(static_cast<char*>(object) + offset);
					set = *static_cast<decay<propertyT>*>(value);
				};

				property_data property{ getter, hash(name), name, get_type_impl<decay<propertyT>>(), setter, specifiers, type };
				add_property_impl(type , &property);
			}
		}

		template<typename T, typename propertyT>
		REFLECTPP_INLINE void registry::add_property(type_data* type, const char* name, propertyT(T::* getter)() const, void(T::* setter)(propertyT), size_t specifiers) REFLECTPP_NOEXCEPT
		{
			if (get_type<T>() != type)
			{
				REFLECTPP_LOG("%s isn't in type", name);
				return;
			}

			auto get = [getter](void* object, bool& is_owner) -> void*
			{
				if constexpr (std::is_reference_v<propertyT>)
				{
					is_owner = false;
					return (void*)(&(static_cast<T*>(object)->*getter)());
				}
				else if constexpr (std::is_pointer_v<propertyT>)
				{
					is_owner = false;
					return (void*)(static_cast<T*>(object)->*getter)();
				}
				else
				{
					is_owner = true;
					return new propertyT((static_cast<T*>(object)->*getter)());
				}
			};

			auto set = [setter](void* object, void* value)
			{
				if constexpr (std::is_pointer_v<propertyT>)
				{
					(static_cast<T*>(object)->*setter)(static_cast<decay<propertyT>*>(value));
				}
				else
				{
					(static_cast<T*>(object)->*setter)(*static_cast<decay<propertyT>*>(value));
				}
			};

			property_data property{ get, hash(name), name, get_type_impl<decay<propertyT>>(), set, specifiers, type };
			add_property_impl(type, &property);
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::add_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || std::is_arithmetic_v<T>)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else if constexpr (!is_registered<T>::value)
			{
				REFLECTPP_LOG("REFLECT() macro isn't used");
				return nullptr;
			}
			else
			{
				return get_type_impl<T>();
			}
		}

		template<typename T, typename U>
		REFLECTPP_INLINE std::remove_pointer_t<T>* registry::cast(U* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (!std::is_pointer_v<T>)
			{
				REFLECTPP_LOG("not a pointer");
				return nullptr;
			}
			else if constexpr (!is_valid_type<std::remove_pointer_t<T>>::value)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else if constexpr (!is_valid_type<U>::value)
			{
				REFLECTPP_LOG("invalid object type");
				return nullptr;
			}
			else
			{
				bool can_cast{ cast_impl(get_type(object), get_type<std::remove_pointer_t<T>>()) };
				return can_cast ? reinterpret_cast<T>(object) : nullptr;
			}
		}

		template<typename T>
		REFLECTPP_INLINE factory_data* registry::get_factory() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else
			{
				factory_data* addr{ get_factory_impl(type_id<T>()) };

				if (addr != nullptr)
					return addr;

				auto constructor = []() -> void*
				{
					if constexpr (std::is_constructible_v<T>)
					{
						return new T();
					}
					else
					{
						return nullptr;
					}
				};

				auto copy = [](void* object) -> void*
				{
					if constexpr (std::is_copy_constructible_v<T>)
					{
						return new T(*static_cast<T*>(object));
					}
					else
					{
						return nullptr;
					}
				};

				auto destructor = [](void* object)
				{
					if constexpr (std::is_destructible_v<T>)
						delete static_cast<T*>(object);
				};

				factory_data factory{ constructor, copy , destructor };
				return add_factory_impl(type_id<T>(), &factory);
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::get_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<T> || is_associative_container<T>::value || is_sequence_container<T>::value)
			{
				return get_type_impl<T>();
			}
			else
			{
				type_data* type{ get_type_impl(type_id<T>()) };

				if (type == nullptr)
				{
					REFLECTPP_LOG("unregistered type");
					return nullptr;
				}

				return type;
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::get_type(T&& object) REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_param<T>::value)
			{
				REFLECTPP_LOG("invalid param");
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<decay<T>> || is_associative_container<decay<T>>::value || is_sequence_container<decay<T>>::value)
			{
				return get_type_impl<decay<T>>();
			}
			else if constexpr (!is_registered<decay<T>>::value)
			{
				REFLECTPP_LOG("unregistered type");
				return nullptr;
			}
			else
			{
				if constexpr (std::is_pointer_v<std::decay_t<T>>)
				{
					if (std::forward<T>(object) == nullptr)
					{
						return get_type_impl(type_id<decay<T>>());
					}
					else
					{
						return get_type_impl(std::forward<T>(object)->get_type_id());
					}
				}
				else
				{
					return get_type_impl(std::forward<T>(object).get_type_id());
				}
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_info_data* registry::get_type_info() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_LOG(false, "invalid type");
				return nullptr;
			}
			else
			{
				type_info_data* addr{ get_type_info_impl(type_id<T>()) };

				if (addr != nullptr)
					return addr;

				type_info_data type_info{ type_id<T>(), type_name<T>() };
				return add_type_info_impl(&type_info);
			}
		}

		template<typename T>
		REFLECTPP_INLINE associative_view_data* registry::get_associative_view_impl() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_associative_container<T>::value)
			{
				return nullptr;
			}
			else if constexpr (std::is_pointer_v<T::value_type>)
			{
				REFLECTPP_LOG("pointer not supported");
				return nullptr;
			}
			else
			{
				associative_view_data* addr{ get_associative_view_impl(type_id<T>()) };

				if (addr != nullptr)
					return addr;

				auto associative_data{ get_associative_container_data(T()) };

				if (associative_data.m_begin == nullptr || associative_data.m_end == nullptr || associative_data.m_size == nullptr)
				{
					REFLECTPP_LOG("begin, end or size function not linked to custom associative container");
					return nullptr;
				}

				using class_type = typename decltype(associative_data)::class_type;
				using iterator = typename decltype(associative_data)::iterator;
				using key_type = typename decltype(associative_data)::key_type;

				associative_view_data associative_view;
				associative_view.m_key_type = get_type_impl<key_type>();

				if constexpr (has_value_type<class_type>::value)
					associative_view.m_value_type = get_type_impl<typename decltype(associative_data)::value_type>();

				associative_view.m_associative_at = [](void* container, size_t index) -> std::pair<void*, void*>
				{
					auto obj{ static_cast<class_type*>(container) };
					auto data{ get_associative_container_data(*obj) };

					for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
					{
						if (i == index)
						{
							if constexpr (has_value_type<class_type>::value)
							{
								//TODO
								return std::make_pair((void*)(&(it->first)), (void*)(&(it->second)));
								//return std::make_pair(static_cast<void*>(&(it->first)), static_cast<void*>(&(it->second)));
							}
							else
							{
								return std::make_pair(static_cast<void*>(const_cast<key_type*>(&(*it))), nullptr);
							}
						}
					}

					return std::make_pair(nullptr, nullptr);
				};

				if (associative_data.m_clear != nullptr)
				{
					associative_view.m_associative_clear = [](void* container)
					{
						auto obj{ static_cast<class_type*>(container) };
						get_associative_container_data(*obj).m_clear(obj);
					};
				}

				if (associative_data.m_equal_range != nullptr)
				{
					associative_view.m_associative_equal_range = [](void* container, void* key)->std::pair<size_t, size_t>
					{
						auto obj{ static_cast<class_type*>(container) };
						auto data{ get_associative_container_data(*obj) };
						auto range{ data.m_equal_range(obj, *static_cast<key_type*>(key)) };

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

				if (associative_data.m_erase != nullptr)
				{
					associative_view.m_associative_erase = [](void* container, void* key) -> size_t
					{
						auto obj{ static_cast<class_type*>(container) };
						return get_associative_container_data(*obj).m_erase(obj, *static_cast<key_type*>(key));
					};
				}

				if (associative_data.m_find != nullptr)
				{
					associative_view.m_associative_find = [](void* container, void* key) -> size_t
					{
						auto obj{ static_cast<class_type*>(container) };
						auto data{ get_associative_container_data(*obj) };
						auto find{ data.m_find(obj, *static_cast<key_type*>(key)) };

						if (find == data.m_begin(obj))
							return data.m_size(obj);

						for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
							if (it == find)
								return i;

						return data.m_size(obj);
					};
				}

				if (associative_data.m_insert != nullptr)
				{
					associative_view.m_associative_insert = [](void* container, void* key, void* value) -> std::pair<size_t, bool>
					{
						auto obj{ static_cast<class_type*>(container) };
						auto data{ get_associative_container_data(*obj) };
						std::pair<iterator, bool> insert;

						if constexpr (has_value_type<class_type>::value)
						{
							using value_type = typename decltype(data)::value_type;
							insert = data.m_insert(obj, *static_cast<key_type*>(key), value != nullptr ? *static_cast<value_type*>(value) : value_type());
						}
						else
						{
							insert = data.m_insert(obj, *static_cast<key_type*>(key));
						}

						for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
							if (it == insert.first)
								return std::make_pair(i, insert.second);

						return std::make_pair(data.m_size(obj), false);
					};
				}

				associative_view.m_associative_size = [](void* container) -> size_t
				{
					auto obj{ static_cast<class_type*>(container) };
					return get_associative_container_data(*obj).m_size(obj);
				};

				return add_associative_view_impl(type_id<T>(), &associative_view);
			}
		}

		template<typename T>
		REFLECTPP_INLINE sequential_view_data* registry::get_sequential_view_impl() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_sequence_container<T>::value)
			{
				return nullptr;
			}
			else if constexpr (std::is_pointer_v<T::value_type>)
			{
				REFLECTPP_LOG("pointer not supported");
				return nullptr;
			}
			else
			{
				sequential_view_data* addr{ get_sequential_view_impl(type_id<T>()) };

				if (addr != nullptr)
					return addr;

				auto sequence_data{ get_sequence_container_data(T()) };

				if (sequence_data.m_begin == nullptr || sequence_data.m_end == nullptr)
				{
					REFLECTPP_LOG("begin or end function not linked to custom sequence container");
					return nullptr;
				}

				using class_type = typename decltype(sequence_data)::class_type;
				using value_type = typename decltype(sequence_data)::value_type;

				sequential_view_data sequential_view;
				sequential_view.m_value_type = get_type_impl<value_type>();

				if (sequence_data.m_at != nullptr)
				{
					sequential_view.m_sequence_assign = [](void* container, size_t index, void* value)
					{
						auto obj{ static_cast<class_type*>(container) };
						get_sequence_container_data(*obj).m_at(obj, index) = *static_cast<value_type*>(value);
					};

					sequential_view.m_sequence_at = [](void* container, size_t index) -> void*
					{
						auto obj{ static_cast<class_type*>(container) };
						return static_cast<void*>(&get_sequence_container_data(*obj).m_at(obj, index));
					};
				}
				else
				{
					sequential_view.m_sequence_assign = [](void* container, size_t index, void* value)
					{
						auto obj{ static_cast<class_type*>(container) };
						auto data{ get_sequence_container_data(*obj) };

						for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
						{
							if (i == index)
							{
								*it = *static_cast<value_type*>(value);
								break;
							}
						}
					};

					sequential_view.m_sequence_at = [](void* container, size_t index) -> void*
					{
						auto obj{ static_cast<class_type*>(container) };
						auto data{ get_sequence_container_data(*obj) };

						for (auto [it, i] = std::tuple{ data.m_begin(obj), 0u }; it != data.m_end(obj); ++it, ++i)
							if (i == index)
								return static_cast<void*>(&(*it));

						return nullptr;
					};
				}

				if (sequence_data.m_clear != nullptr)
				{
					sequential_view.m_sequence_clear = [](void* container)
					{
						auto obj{ static_cast<class_type*>(container) };
						get_sequence_container_data(*obj).m_clear(obj);
					};
				}

				if (sequence_data.m_erase != nullptr)
				{
					sequential_view.m_sequence_erase = [](void* container, size_t index)
					{
						auto obj{ static_cast<class_type*>(container) };
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

				if (sequence_data.m_insert != nullptr)
				{
					sequential_view.m_sequence_insert = [](void* container, size_t index, void* value)
					{
						auto obj{ static_cast<class_type*>(container) };
						auto val{ static_cast<value_type*>(value) };
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

				if (sequence_data.m_resize != nullptr)
				{
					sequential_view.m_sequence_resize = [](void* container, size_t size)
					{
						auto obj{ static_cast<class_type*>(container) };
						get_sequence_container_data(*obj).m_resize(obj, size);
					};
				}

				if (sequence_data.m_size != nullptr)
				{
					sequential_view.m_sequence_size = [](void* container) -> size_t
					{
						auto obj{ static_cast<class_type*>(container) };
						return get_sequence_container_data(*obj).m_size(obj);
					};
				}
				else
				{
					sequential_view.m_sequence_size = [](void* container) -> size_t
					{
						size_t size{ 0 };

						for (auto& it : *static_cast<class_type*>(container))
						{
							(void)it;
							++size;
						}

						return size;
					};
				}

				return add_sequential_view_impl(type_id<T>(), &sequential_view);
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::get_type_impl() REFLECTPP_NOEXCEPT
		{
			type_data* addr{ get_type_impl(type_id<T>()) };

			if (addr != nullptr)
				return addr;

			type_data type;
			type.m_associative_view = get_associative_view_impl<T>();
			type.m_factory = get_factory<T>();
			type.m_is_arithmetic = std::is_arithmetic_v<T>;
			type.m_sequential_view = get_sequential_view_impl<T>();
			type.m_size = sizeof(T);
			type.m_type_info = get_type_info<T>();

			return add_type_impl(&type);
		}
	}
}
