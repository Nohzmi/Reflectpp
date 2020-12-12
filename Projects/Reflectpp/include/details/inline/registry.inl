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
				type* base{ add_base_impl(_type, get_type_impl<T>()) };
				REFLECTPP_ASSERT(base != nullptr, "base type already registered");

				return base;
			}
		}

		template<typename T, typename propertyT, typename U>
		REFLECTPP_INLINE property* registry::add_property(type* _type, const char* name, propertyT T::* addr) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "%s isn't in type", name);

			property* prop { add_property_impl(_type, name, (size_t)(char*)&((T*)nullptr->*addr), get_type_impl<U>()) };
			REFLECTPP_ASSERT(prop != nullptr, "%s already registered", name);

			return prop;
		}

		template<typename T, typename propertyT, typename U>
		REFLECTPP_INLINE property* registry::add_property(type* _type, const char* name, propertyT(T::* getter)() const, void(T::* setter)(propertyT)) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "%s isn't in type", name);

			auto get = [getter](void* object, bool& is_owner) -> void*
			{
				if constexpr (std::is_reference_v<propertyT>)
				{
					is_owner = false;
					const U& tmp{ (static_cast<T*>(object)->*getter)() };

					return const_cast<U*>(&tmp);
				}
				else
				{
					is_owner = true;
					U* val{ new U() };
					*val = (static_cast<T*>(object)->*getter)();

					return  val;
				}
			};

			auto set = [setter](void* object, void* value)
			{
				(static_cast<T*>(object)->*setter)(*static_cast<U*>(value));
			};

			property* prop { add_property_impl(_type, name, get, set, get_type_impl<U>()) };
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
				bool can_cast{ cast_impl(get_type<std::remove_pointer_t<T>>(), get_type(object)) };
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

				return add_factory_impl(type_id<T>(), constructor, copy, destructor);
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
