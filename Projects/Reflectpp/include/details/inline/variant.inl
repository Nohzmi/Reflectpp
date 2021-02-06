// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename>
	REFLECTPP_INLINE variant::variant(T&& object) REFLECTPP_NOEXCEPT
	{
		m_data.m_is_owner = !std::is_reference_v<T>;
		m_data.m_type = details::registry::get_instance().get_type(object);

		if constexpr (std::is_reference_v<T>)
		{
			m_data.m_value = &object;
		}
		else
		{
			m_data.m_value = new T(std::forward<T>(object));
		}
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::can_convert() const REFLECTPP_NOEXCEPT
	{
		if (!is_valid())
			return false;

		if constexpr (std::is_arithmetic_v<T>)
		{
			if constexpr (std::is_same_v<T, bool>) return m_data.m_type->m_utility->m_can_convert_to_bool;
			else if constexpr (std::is_same_v<T, double>) return m_data.m_type->m_utility->m_can_convert_to_double;
			else if constexpr (std::is_same_v<T, float>) return m_data.m_type->m_utility->m_can_convert_to_float;
			else if constexpr (std::is_same_v<T, int>) return m_data.m_type->m_utility->m_can_convert_to_int;
			else if constexpr (std::is_same_v<T, int8_t>) return m_data.m_type->m_utility->m_can_convert_to_int8;
			else if constexpr (std::is_same_v<T, int16_t>) return m_data.m_type->m_utility->m_can_convert_to_int16;
			else if constexpr (std::is_same_v<T, int32_t>) return m_data.m_type->m_utility->m_can_convert_to_int32;
			else if constexpr (std::is_same_v<T, int64_t>) return m_data.m_type->m_utility->m_can_convert_to_int64;
			else if constexpr (std::is_same_v<T, uint8_t>) return m_data.m_type->m_utility->m_can_convert_to_uint8;
			else if constexpr (std::is_same_v<T, uint16_t>) return m_data.m_type->m_utility->m_can_convert_to_uint16;
			else if constexpr (std::is_same_v<T, uint32_t>) return m_data.m_type->m_utility->m_can_convert_to_uint32;
			else if constexpr (std::is_same_v<T, uint64_t>) return m_data.m_type->m_utility->m_can_convert_to_uint64;
		}
		else
		{
			return is_valid() ? details::registry::get_instance().can_cast<T>(m_data.m_type) : false;
		}
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::convert() REFLECTPP_NOEXCEPT
	{
		if (!is_valid() || !can_convert<T>())
			return false;

		if constexpr (std::is_arithmetic_v<T>)
		{
			void* value{ nullptr };

			if constexpr (std::is_same_v<T, bool>) value = m_data.m_type->m_utility->m_convert_to_bool(m_data.m_value);
			else if constexpr (std::is_same_v<T, double>) value = m_data.m_type->m_utility->m_convert_to_double(m_data.m_value);
			else if constexpr (std::is_same_v<T, float>) value = m_data.m_type->m_utility->m_convert_to_float(m_data.m_value);
			else if constexpr (std::is_same_v<T, int>) value = m_data.m_type->m_utility->m_convert_to_int(m_data.m_value);
			else if constexpr (std::is_same_v<T, int8_t>) value = m_data.m_type->m_utility->m_convert_to_int8(m_data.m_value);
			else if constexpr (std::is_same_v<T, int16_t>) value = m_data.m_type->m_utility->m_convert_to_int16(m_data.m_value);
			else if constexpr (std::is_same_v<T, int32_t>) value = m_data.m_type->m_utility->m_convert_to_int32(m_data.m_value);
			else if constexpr (std::is_same_v<T, int64_t>) value = m_data.m_type->m_utility->m_convert_to_int64(m_data.m_value);
			else if constexpr (std::is_same_v<T, uint8_t>) value = m_data.m_type->m_utility->m_convert_to_uint8(m_data.m_value);
			else if constexpr (std::is_same_v<T, uint16_t>) value = m_data.m_type->m_utility->m_convert_to_uint16(m_data.m_value);
			else if constexpr (std::is_same_v<T, uint32_t>) value = m_data.m_type->m_utility->m_convert_to_uint32(m_data.m_value);
			else if constexpr (std::is_same_v<T, uint64_t>) value = m_data.m_type->m_utility->m_convert_to_uint64(m_data.m_value);

			if (m_data.m_is_owner)
				clear();

			m_data.m_is_owner = true;
			m_data.m_type = details::registry::get_instance().get_type<T>();
			m_data.m_value = value;
		}
		else
		{
			m_data.m_type = details::registry::get_instance().get_type<std::remove_pointer_t<T>>();
		}

		return true;
	}

	template<typename T>
	REFLECTPP_INLINE T& variant::get_value() REFLECTPP_NOEXCEPT
	{
		return *static_cast<T*>(m_data.m_value);
	}

	template<typename T>
	REFLECTPP_INLINE const T& variant::get_value() const REFLECTPP_NOEXCEPT
	{
		return *static_cast<T*>(m_data.m_value);
	}

	template<typename T>
	REFLECTPP_INLINE bool variant::is_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? details::registry::get_instance().get_type<T>() == m_data.m_type : false;
	}
}
