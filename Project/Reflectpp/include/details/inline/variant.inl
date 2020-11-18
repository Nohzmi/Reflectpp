// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/utilities.h"
#include "type.h"

namespace reflectpp
{
	template<typename T>
	inline variant::variant(T* object) noexcept :
		m_data{ object },
		m_is_owner{ false },
		m_type{ &type::get(object) }
	{
	}

	template<typename T>
	inline T& variant::get_value() noexcept
	{
		details::_assert(is_valid(), "variant::get_value<%s>() : invalid variant\n", details::type_name<T>());
		details::_assert(type::get<T>() == *m_type, "variant::get_value<%s>() : wrong type, stored value is a %s\n", details::type_name<T>(), m_type->get_name());

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	inline const T& variant::get_value() const noexcept
	{
		details::_assert(is_valid(), "variant::get_value<%s>() : invalid variant\n", details::type_name<T>());
		details::_assert(type::get<T>() == *m_type, "variant::get_value<%s>() : wrong type, stored value is a %s\n", details::type_name<T>(), m_type->get_name());

		return *static_cast<T*>(m_data);
	}

	template<typename T>
	inline bool variant::is_type() const noexcept
	{
		return is_valid() ? type::get<T>() == *m_type : false;
	}
}
