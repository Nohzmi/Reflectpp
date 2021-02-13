// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		REFLECTPP_INLINE auto property_getter_addr(size_t offset) REFLECTPP_NOEXCEPT
		{
			return [offset](void* object, bool& is_owner) -> void*
			{
				is_owner = false;
				return static_cast<char*>(object) + offset;
			};
		}

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto property_getter_func(PropertyT(T::* getter)() const) REFLECTPP_NOEXCEPT
		{
			return [getter](void* object, bool& is_owner) -> void*
			{
				if constexpr (std::is_reference_v<PropertyT>)
				{
					is_owner = false;
					return (void*)(&(static_cast<T*>(object)->*getter)());
				}
				else if constexpr (std::is_pointer_v<PropertyT>)
				{
					is_owner = false;
					return (void*)(static_cast<T*>(object)->*getter)();
				}
				else
				{
					is_owner = true;
					return new PropertyT((static_cast<T*>(object)->*getter)());
				}
			};
		}

		template<typename PropertyT>
		REFLECTPP_INLINE auto property_setter_addr(size_t offset) REFLECTPP_NOEXCEPT
		{
			return [offset](void* object, void* value)
			{
				auto& set = *reinterpret_cast<decay<PropertyT>*>(static_cast<char*>(object) + offset);
				set = *static_cast<decay<PropertyT>*>(value);
			};
		}

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto property_setter_func(void(T::* setter)(PropertyT)) REFLECTPP_NOEXCEPT
		{
			return [setter](void* object, void* value)
			{
				if constexpr (std::is_pointer_v<PropertyT>)
				{
					(static_cast<T*>(object)->*setter)(static_cast<decay<PropertyT>*>(value));
				}
				else
				{
					(static_cast<T*>(object)->*setter)(*static_cast<decay<PropertyT>*>(value));
				}
			};
		}
	}
}
