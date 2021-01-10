// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE type* registry::add_base(type* _type) REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || std::is_arithmetic_v<T>)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else
			{
				type* base{ add_base_impl(get_type_impl<T>(), _type) };
				REFLECTPP_ASSERT(base != nullptr, "base type already registered");

				return base;
			}
		}

		template<typename T, typename propertyT>
		REFLECTPP_INLINE property* registry::add_property(propertyT T::* addr, const char* name, size_t specifiers, type* _type) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "%s isn't in type", name);

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

			property* prop { add_property_impl(getter, name, get_type_impl<decay<propertyT>>(), setter, specifiers, _type) };
			REFLECTPP_ASSERT(prop != nullptr, "%s already registered", name);

			return prop;
		}

		template<typename T, typename propertyT>
		REFLECTPP_INLINE property* registry::add_property(propertyT(T::* getter)() const, const char* name, void(T::* setter)(propertyT), size_t specifiers, type* _type) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "%s isn't in type", name);

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
					(static_cast<T*>(object)->*setter)(static_cast<decay<propertyT>*>(value));
				else
					(static_cast<T*>(object)->*setter)(*static_cast<decay<propertyT>*>(value));

			};
			
			property* prop { add_property_impl(get, name, get_type_impl<decay<propertyT>>(), set, specifiers, _type) };
			REFLECTPP_ASSERT(prop != nullptr, "%s already registered", name);

			return prop;
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::add_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || std::is_arithmetic_v<T>)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else if constexpr (!is_registered<T>::value)
			{
				REFLECTPP_ASSERT(false, "REFLECT() macro isn't used");
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
				REFLECTPP_ASSERT(false, "not a pointer");
				return nullptr;
			}
			else if constexpr (!is_valid_type<std::remove_pointer_t<T>>::value)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else if constexpr (!is_valid_type<U>::value)
			{
				REFLECTPP_ASSERT(false, "invalid object type");
				return nullptr;
			}
			else
			{
				bool can_cast{ cast_impl(get_type(object), get_type<std::remove_pointer_t<T>>()) };
				return can_cast ? reinterpret_cast<T>(object) : nullptr;
			}
		}

		template<typename T>
		REFLECTPP_INLINE factory* registry::get_factory() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else
			{
				factory* factory{ get_factory_impl(type_id<T>()) };

				if (factory != nullptr)
					return factory;

				auto constructor = []() -> void*
				{
					if constexpr (std::is_constructible_v<T>)
						return new T();
					else
						return nullptr;
				};

				auto copy = [](void* object) -> void*
				{
					if constexpr (std::is_copy_constructible_v<T>)
						return new T(*static_cast<T*>(object));
					else
						return nullptr;
				};

				auto destructor = [](void* object)
				{
					if constexpr (std::is_destructible_v<T>)
						delete static_cast<T*>(object);
				};

				return add_factory_impl(constructor, copy, destructor, type_id<T>());
			}
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::get_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<T>)
			{
				return get_type_impl<T>();
			}
			else
			{
				type* _type{ get_type_impl(type_id<T>()) };
				REFLECTPP_ASSERT(_type != nullptr, "unregistered type");

				return _type;
			}
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::get_type(T&& object) REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_param<T>::value)
			{
				REFLECTPP_ASSERT(false, "invalid param");
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<decay<T>>)
			{
				return get_type_impl<decay<T>>();
			}
			else if constexpr (!is_registered<decay<T>>::value)
			{
				REFLECTPP_ASSERT(false, "unregistered type");
				return nullptr;
			}
			else
			{
				if constexpr (std::is_pointer_v<std::decay_t<T>>)
				{
					if (std::forward<T>(object) == nullptr)
						return get_type_impl(type_id<decay<T>>());
					else
						return get_type_impl(std::forward<T>(object)->get_type_id());
				}
				else
				{
					return get_type_impl(std::forward<T>(object).get_type_id());
				}
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_info* registry::get_type_info() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value)
			{
				REFLECTPP_ASSERT(false, "invalid type");
				return nullptr;
			}
			else
			{
				type_info* type_info{ get_type_info_impl(type_id<T>()) };

				if (type_info != nullptr)
					return type_info;

				return add_type_info(type_id<T>(), type_name<T>());
			}
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::get_type_impl() REFLECTPP_NOEXCEPT
		{
			type* type{ get_type_impl(type_id<T>()) };

			if (type == nullptr)
				return add_type_impl(get_factory<T>(), sizeof(T), get_type_info<T>());

			return type;
		}
	}
}
