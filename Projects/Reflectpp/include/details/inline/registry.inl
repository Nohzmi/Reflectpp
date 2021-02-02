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
					//type->m_enumeration->m_declaring_type TODO
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
				auto data{ add_property_impl(type, id) };

				if (data != nullptr)
				{
					data->m_declaring_type = type;
					data->m_getter = get_getter_addr(offset);
					data->m_id = id;
					data->m_name = name;
					data->m_setter = get_setter_addr<PropertyT>(offset);
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
			auto data{ add_property_impl(type, id) };

			if (data != nullptr)
			{
				data->m_declaring_type = type;
				data->m_getter = get_getter_func<T, PropertyT>(getter);
				data->m_id = id;
				data->m_name = name;
				data->m_setter = get_setter_func<T, PropertyT>(setter);
				data->m_specifiers = specifiers;
				data->m_type = add_type_impl<decay<PropertyT>>();
			}
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
			if (type->m_enumeration == nullptr || name == nullptr)
				return;

			type->m_enumeration->m_names.emplace_back(name);
			type->m_enumeration->m_values.emplace_back(static_cast<size_t>(value));
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
				bool created{ false };
				auto data{ get_factory_impl(type_id<T>(), created) };

				if (created)
				{
					data->m_constructor = get_constructor<T>();
					data->m_copy = get_copy_constructor<T>();
					data->m_destructor = get_destructor<T>();
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
			else if constexpr (std::is_arithmetic_v<T> || is_associative_container<T>::value || is_sequence_container<T>::value)
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
			else if constexpr (std::is_arithmetic_v<decay<T>> || is_associative_container<decay<T>>::value || is_sequence_container<decay<T>>::value)
			{
				return add_type_impl<decay<T>>();
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

					data->m_associative_at = get_associative_at<class_type, key_type>();
					data->m_associative_clear = associative_data.m_clear != nullptr ? get_associative_clear<class_type>() : nullptr;
					data->m_associative_equal_range = associative_data.m_equal_range != nullptr ? get_associative_equal_range<class_type, key_type>() : nullptr;
					data->m_associative_erase = associative_data.m_erase != nullptr ? get_associative_erase<class_type, key_type>() : nullptr;
					data->m_associative_find = associative_data.m_find != nullptr ? get_associative_find<class_type, key_type>() : nullptr;
					if constexpr (!has_value_type<class_type>::value) data->m_associative_insert = get_associative_insert<class_type, iterator, key_type>();
					else data->m_associative_insert = get_associative_insert<class_type, iterator, key_type, typename decltype(associative_data)::value_type>();
					data->m_associative_size = get_associative_size<class_type>();
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

					data->m_sequence_assign = sequence_data.m_at != nullptr ? get_sequence_assign<class_type, value_type>() : get_sequence_assign_impl<class_type, value_type>();
					data->m_sequence_at = sequence_data.m_at != nullptr ? get_sequence_at<class_type>() : get_sequence_at_impl<class_type>();
					data->m_sequence_clear = sequence_data.m_clear != nullptr ? get_sequence_clear<class_type>() : nullptr;
					data->m_sequence_erase = sequence_data.m_erase != nullptr ? get_sequence_erase<class_type>() : nullptr;
					data->m_sequence_insert = sequence_data.m_insert != nullptr ? get_sequence_insert<class_type, value_type>() : nullptr;
					data->m_sequence_resize = sequence_data.m_resize != nullptr ? get_sequence_resize<class_type>() : nullptr;
					data->m_sequence_size = sequence_data.m_size != nullptr ? get_sequence_size<class_type>() : get_sequence_size_impl<class_type>();
					data->m_value_type = add_type_impl<value_type>();
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
			}

			return data;
		}
	}
}
