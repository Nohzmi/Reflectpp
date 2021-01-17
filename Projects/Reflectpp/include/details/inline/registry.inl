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
			else if constexpr (std::is_arithmetic_v<T>)
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
			else if constexpr (std::is_arithmetic_v<decay<T>>)
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
		REFLECTPP_INLINE type_data* registry::get_type_impl() REFLECTPP_NOEXCEPT
		{
			type_data* addr{ get_type_impl(type_id<T>()) };

			if (addr != nullptr)
				return addr;

			type_data type;
			type.m_factory = get_factory<T>();
			type.m_size = sizeof(T);
			type.m_type_info = get_type_info<T>();

			if constexpr (is_sequence_container<T>::value)
			{
				if constexpr (std::is_pointer_v<T::value_type>)
				{
					REFLECTPP_LOG("pointer not supported");
					return nullptr;
				}
				else
				{
					type.m_sequence_assign = [](void* container, size_t index, void* value)
					{
						auto& set = *static_cast<typename T::value_type*>(&static_cast<T*>(container)->at(index));
						set = *static_cast<typename T::value_type*>(value);
					};

					type.m_sequence_at = [](void* container, size_t index) -> void*
					{
						return static_cast<void*>(&static_cast<T*>(container)->at(index));
					};

					type.m_sequence_clear = [](void* container)
					{
						static_cast<T*>(container)->clear();
					};

					type.m_sequence_erase = [](void* container, size_t index)
					{
						static_cast<T*>(container)->erase(static_cast<T*>(container)->begin() + index);
					};

					type.m_sequence_insert = [](void* container, size_t index, void* value)
					{
						static_cast<T*>(container)->insert(static_cast<T*>(container)->begin() + index, *static_cast<typename T::value_type*>(value));
					};

					type.m_sequence_resize = [](void* container, size_t size)
					{
						static_cast<T*>(container)->resize(size);
					};

					type.m_sequence_size = [](void* container) -> size_t
					{
						return static_cast<T*>(container)->size();
					};

					type.m_is_sequence_container = true;
					type.m_value_type = get_type_impl<T::value_type>();

					return add_type_impl(&type);
				}
			}
			else
			{
				return add_type_impl(&type);
			}
		}
	}
}
