// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE type* registry::add_base(type* _type) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !is_valid<T>::value)
			{
				REFLECTPP_ASSERT(false, "registration::base<%s>() : invalid type\n", type_name<T>());
				return nullptr;
			}
			else
			{
				type* base{ add_base(_type, get_type_with_initialization<T>()) };
				REFLECTPP_ASSERT(base != nullptr, "registration::base<%s>() : base type already registered\n", get_type_name(base));

				return base;
			}
		}

		template<typename T, typename propertyT, typename U>
		REFLECTPP_INLINE property* registry::add_property(type* _type, const char* name, propertyT T::* addr) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "registration::property(const char* name, %s %s::* addr) : %s isn't in %s\n", type_name<U>(), type_name<T>(), name, get_type_name(_type));

			property* prop { add_property(_type, name, (size_t)(char*)&((T*)nullptr->*addr), get_type_with_initialization<U>()) };
			REFLECTPP_ASSERT(prop != nullptr, "registration::property(const char* name, %s %s::* addr) : %s already registered\n", type_name<U>(), type_name<T>(), name);

			return prop;
		}

		template<typename T, typename propertyT, typename U>
		REFLECTPP_INLINE property* registry::add_property(type* _type, const char* name, propertyT(T::* getter)() const, void(T::* setter)(propertyT)) REFLECTPP_NOEXCEPT
		{
			REFLECTPP_ASSERT(get_type<T>() == _type, "registration::property(const char* name, %s %s::* addr) : %s isn't in %s\n", type_name<U>(), type_name<T>(), name, get_type_name(_type));

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

			property* prop { add_property(_type, name, get, set, get_type_with_initialization<U>()) };
			REFLECTPP_ASSERT(prop != nullptr, "registration::property(const char* name, %s %s::* addr) : %s already registered\n", type_name<U>(), type_name<T>(), name);

			return prop;
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::add_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !is_valid<T>::value)
			{
				REFLECTPP_ASSERT(false, "registration::class_<%s>() : invalid type\n", type_name<T>());
				return nullptr;
			}
			else if constexpr (!use_macro<T>::value)
			{
				REFLECTPP_ASSERT(false, "registration::class_<%s>() : REFLECT(T) macro isn't used\n", type_name<T>());
				return nullptr;
			}
			else
			{
				type* type{ get_type(type_id<T>()) };

				if (type == nullptr)
					return add_type(get_factory<T>(), sizeof(T), get_type_info<T>());

				return type;
			}
		}

		template<typename T, typename U, typename V>
		REFLECTPP_INLINE std::remove_pointer_t<T>* registry::cast(U* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (!std::is_pointer_v<T>)
			{
				REFLECTPP_ASSERT(false, "type::cast<%s>(%s*& object) : not a pointer\n", type_name<T>(), type_name(object));
				return nullptr;
			}
			else if constexpr (std::is_const_v<V> || std::is_pointer_v<V> || std::is_void_v<V> || std::is_volatile_v<V>)
			{
				REFLECTPP_ASSERT(false, "type::cast<%s>(%s*& object) : invalid type\n", type_name<T>(), type_name(object));
				return nullptr;
			}
			else if constexpr (std::is_const_v<U> || std::is_void_v<U> || std::is_volatile_v<U>)
			{
				REFLECTPP_ASSERT(false, "type::cast<%s>(%s*& object) : invalid object type\n", type_name<T>(), type_name(object));
				return nullptr;
			}
			else
				return cast(get_type<V>(), get_type(object)) ? reinterpret_cast<T>(object) : nullptr;
		}

		template<typename T>
		REFLECTPP_INLINE factory* registry::get_factory() REFLECTPP_NOEXCEPT
		{
			factory* factory{ get_factory(type_id<T>()) };

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

			return add_factory(type_id<T>(), constructor, copy, destructor);
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::get_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid<T>::value)
			{
				REFLECTPP_ASSERT(false, "type::get<%s>() : invalid type\n", type_name<T>());
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<T>)
			{
				type* type{ get_type(type_id<T>()) };

				if (type == nullptr)
					return add_type(get_factory<T>(), sizeof(T), get_type_info<T>());

				return type;
			}
			else
			{
				type* type{ get_type(type_id<T>()) };
				REFLECTPP_ASSERT(type != nullptr, "type::get<%s>() : unregistered type\n", type_name<T>());

				return type;
			}
		}

		template<typename T>
		REFLECTPP_INLINE type* registry::get_type(T* object) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_null_pointer_v<T> || std::is_void_v<T> || std::is_volatile_v<T>)
			{
				REFLECTPP_ASSERT(false, "type::get(%s*& object) : invalid type\n", type_name<T>());
				return nullptr;
			}
			else if constexpr (!std::is_arithmetic_v<T> && !use_macro<T>::value)
			{
				REFLECTPP_ASSERT(false, "type::get(%s*& object) : unregistered type\n", type_name(object));
				return nullptr;
			}
			else if constexpr (std::is_arithmetic_v<T>)
			{
				REFLECTPP_ASSERT(object != nullptr, "type::get(%s*& object) : object nullptr\n", type_name<T>());

				type* type{ get_type(type_id<T>()) };

				if (type == nullptr)
					return add_type(get_factory<T>(), sizeof(T), get_type_info<T>());

				return type;
			}
			else
			{
				REFLECTPP_ASSERT(object != nullptr, "type::get(%s*& object) : object nullptr\n", type_name<T>());
				return get_type(type_id(object));
			}
		}
		template<typename T>
		REFLECTPP_INLINE type* registry::get_type_with_initialization() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid<T>::value)
			{
				REFLECTPP_ASSERT(false, "type::get<%s>() : invalid type\n", type_name<T>());
				return nullptr;
			}
			else
			{
				type* type{ get_type(type_id<T>()) };

				if (type == nullptr)
					return add_type(get_factory<T>(), sizeof(T), get_type_info<T>());

				return type;
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_info* registry::get_type_info() REFLECTPP_NOEXCEPT
		{
			type_info* type_info{ get_type_info(type_id<T>()) };

			if (type_info != nullptr)
				return type_info;

			return add_type_info(type_id<T>(), type_name<T>());
		}
	}
}
