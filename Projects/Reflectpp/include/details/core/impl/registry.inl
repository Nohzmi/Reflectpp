// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE void registry::add_base(type_data* type) REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || is_auto_register_type<T>::value || is_enum_type<T>::value)
			{
				REFLECTPP_LOG("invalid type");
			}
			else if constexpr (!has_registered<T>::value)
			{
				REFLECTPP_LOG("REFLECT(T) macro isn't used");
				return nullptr;
			}
			else
			{
				add_base_impl(type, add_type_impl<T>());
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::add_enumeration(const char* name) REFLECTPP_NOEXCEPT
		{
			if constexpr (!std::is_enum_v<T>)
			{
				REFLECTPP_LOG("not an enum");
				return nullptr;
			}
			else if constexpr (std::is_convertible_v<T, int>)
			{
				REFLECTPP_LOG("unscoped enum not supported");
				return nullptr;
			}
			else
			{
				type_data* type{ add_type_impl<T>() };

				if (type != nullptr)
				{
					type->m_enumeration = add_enumeration_impl(type_id<T>());
					type->m_enumeration->m_convert_to_type = utility_convert<std::underlying_type_t<T>, T>();
					type->m_enumeration->m_convert_to_underlying_type = utility_convert<T, std::underlying_type_t<T>>();
					type->m_enumeration->m_name = name;
					type->m_enumeration->m_underlying_type = add_type_impl<std::underlying_type_t<T>>();
				}

				return type;
			}
		}

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE void registry::add_property(type_data* type, const char* name, PropertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_pointer_v<PropertyT>)
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

				size_t id{ hash(name) };
				size_t offset = (size_t)(char*)&((T*)nullptr->*addr);
				auto data{ add_property_impl(type, id, name) };

				if (data != nullptr)
				{
					data->m_declaring_type = type;
					data->m_getter = property_getter_addr(offset);
					data->m_id = id;
					data->m_name = name;
					data->m_setter = property_setter_addr<PropertyT>(offset);
					data->m_specifiers = specifiers;
					data->m_type = add_type_impl<decay<PropertyT>>();
				}
			}
		}

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE void registry::add_property(type_data* type, const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers) REFLECTPP_NOEXCEPT
		{
			if (get_type<T>() != type)
			{
				REFLECTPP_LOG("%s isn't in type", name);
				return;
			}

			size_t id{ hash(name) };
			auto data{ add_property_impl(type, id, name) };

			if (data != nullptr)
			{
				data->m_declaring_type = type;
				data->m_getter = property_getter_func<T, PropertyT>(getter);
				data->m_id = id;
				data->m_name = name;
				data->m_setter = property_setter_func<T, PropertyT>(setter);
				data->m_specifiers = specifiers;
				data->m_type = add_type_impl<decay<PropertyT>>();
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::add_type() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_valid_type<T>::value || is_auto_register_type<T>::value || is_enum_type<T>::value)
			{
				REFLECTPP_LOG("invalid type");
				return nullptr;
			}
			else if constexpr (!has_registered<T>::value)
			{
				REFLECTPP_LOG("REFLECT(T) macro isn't used");
				return nullptr;
			}
			else
			{
				return add_type_impl<T>();
			}
		}

		template<typename EnumT>
		REFLECTPP_INLINE void registry::add_value(type_data* type, const char* name, EnumT value) REFLECTPP_NOEXCEPT
		{
			add_value_impl(type->m_enumeration, name, type->m_enumeration->m_underlying_type->m_factory->m_copy(static_cast<void*>(&value)));
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
				bool created{ false };
				auto data{ get_factory_impl(type_id<T>(), created) };

				if (created)
				{
					data->m_constructor = factory_constructor<T>();
					data->m_copy = factory_copy_constructor<T>();
					data->m_destructor = factory_destructor<T>();
				}

				return data;
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
			else if constexpr (is_auto_register_type<T>::value)
			{
				return add_type_impl<T>();
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
			else if constexpr (is_auto_register_type<decay<T>>::value || is_enum_type<decay<T>>::value)
			{
				return get_type<decay<T>>();
			}
			else if constexpr (!has_registered<decay<T>>::value)
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
				bool created{ false };
				auto data{ get_type_info_impl(type_id<T>(), created) };

				if (created)
				{
					data->m_id = type_id<T>();
					data->m_name = type_name<T>();
				}

				return data;
			}
		}

		template<typename T>
		REFLECTPP_INLINE type_data* registry::add_type_impl() REFLECTPP_NOEXCEPT
		{
			bool created{ false };
			auto data{ add_type_impl(type_id<T>(), created) };

			if (created)
			{
				data->m_associative_view = get_associative_view_impl<T>();
				data->m_factory = get_factory<T>();
				data->m_is_arithmetic = std::is_arithmetic_v<T>;
				data->m_sequential_view = get_sequential_view_impl<T>();
				data->m_size = sizeof(T);
				data->m_type_info = get_type_info<T>();
				data->m_utility = get_utility_impl<T>();
				data->m_wrapper = get_wrapper_impl<T>();
			}

			return data;
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
				bool created{ false };
				auto data{ get_associative_view_impl(type_id<T>(), created) };
				
				if (created)
				{
					auto associative_data{ get_associative_container_data(T()) };

					if (associative_data.m_begin == nullptr || associative_data.m_end == nullptr || associative_data.m_size == nullptr)
					{
						REFLECTPP_LOG("begin, end or size function not linked to custom associative container");
						return nullptr;
					}

					using class_type = typename decltype(associative_data)::class_type;
					using iterator = typename decltype(associative_data)::iterator;
					using key_type = typename decltype(associative_data)::key_type;

					data->m_at = associative_view_at<class_type, key_type>();
					data->m_clear = associative_data.m_clear != nullptr ? associative_view_clear<class_type>() : nullptr;
					data->m_equal_range = associative_data.m_equal_range != nullptr ? associative_view_equal_range<class_type, key_type>() : nullptr;
					data->m_erase = associative_data.m_erase != nullptr ? associative_view_erase<class_type, key_type>() : nullptr;
					data->m_find = associative_data.m_find != nullptr ? associative_view_find<class_type, key_type>() : nullptr;
					if constexpr (!has_value_type<class_type>::value) data->m_insert = associative_view_insert<class_type, iterator, key_type>();
					else data->m_insert = associative_view_insert<class_type, iterator, key_type, typename decltype(associative_data)::value_type>();
					data->m_size = associative_view_size<class_type>();
					data->m_key_type = add_type_impl<key_type>();
					if constexpr (has_value_type<class_type>::value) data->m_value_type = add_type_impl<typename decltype(associative_data)::value_type>();
				}

				return data;
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
				bool created{ false };
				auto data{ get_sequential_view_impl(type_id<T>(), created) };

				if (created)
				{
					auto sequence_data{ get_sequence_container_data(T()) };

					if (sequence_data.m_begin == nullptr || sequence_data.m_end == nullptr)
					{
						REFLECTPP_LOG("begin or end function not linked to custom sequence container");
						return nullptr;
					}

					using class_type = typename decltype(sequence_data)::class_type;
					using value_type = typename decltype(sequence_data)::value_type;

					data->m_assign = sequence_data.m_at != nullptr ? sequential_view_assign<class_type, value_type>() : sequential_view_assign_impl<class_type, value_type>();
					data->m_at = sequence_data.m_at != nullptr ? sequential_view_at<class_type>() : sequential_view_at_impl<class_type>();
					data->m_clear = sequence_data.m_clear != nullptr ? sequential_view_clear<class_type>() : nullptr;
					data->m_erase = sequence_data.m_erase != nullptr ? sequential_view_erase<class_type>() : nullptr;
					data->m_insert = sequence_data.m_insert != nullptr ? sequential_view_insert<class_type, value_type>() : nullptr;
					data->m_resize = sequence_data.m_resize != nullptr ? sequential_view_resize<class_type>() : nullptr;
					data->m_size = sequence_data.m_size != nullptr ? sequential_view_size<class_type>() : sequential_view_size_impl<class_type>();
					data->m_value_type = add_type_impl<value_type>();
				}

				return data;
			}
		}

		template<typename T>
		REFLECTPP_INLINE utility_data* registry::get_utility_impl() REFLECTPP_NOEXCEPT
		{
			bool created{ false };
			auto data{ get_utility_impl(type_id<T>(), created) };

			if (created)
			{
				std::apply([&](auto... args){ (data->m_can_convert_from.emplace_back(std::is_convertible_v<decltype(args), T>), ...); }, m_arithmetic_types);
				std::apply([&](auto... args){ (data->m_can_convert_to.emplace_back(std::is_convertible_v<T, decltype(args)>), ...); }, m_arithmetic_types);
				data->m_compare = utility_compare<T>();
				std::apply([&](auto... args){ (data->m_convert_from.emplace_back(utility_convert<decltype(args), T>()), ...); }, m_arithmetic_types);
				std::apply([&](auto... args){ (data->m_convert_to.emplace_back(utility_convert<T, decltype(args)>()), ...); }, m_arithmetic_types);
			}

			return data;
		}

		template<typename T>
		REFLECTPP_INLINE wrapper_data* registry::get_wrapper_impl() REFLECTPP_NOEXCEPT
		{
			if constexpr (!is_smart_pointer<T>::value)
			{
				return nullptr;
			}
			else
			{
				bool created{ false };
				auto data{ get_wrapper_impl(type_id<T>(), created) };

				if (created)
				{
					auto smart_pointer_obj{ T() };
					auto smart_pointer_data{ get_smart_pointer_data(&smart_pointer_obj) };

					if (smart_pointer_data.m_get == nullptr)
					{
						REFLECTPP_LOG("get function not linked to custom smart pointer");
						return nullptr;
					}

					using class_type = typename decltype(smart_pointer_data)::class_type;
					using value_type = typename decltype(smart_pointer_data)::value_type;

					data->m_get = wrapper_get<class_type>();
					data->m_value_type = add_type_impl<value_type>();
				}

				return data;
			}
		}
	}
}
