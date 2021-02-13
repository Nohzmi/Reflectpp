// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_traits.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <type_traits>

#include "custom_associative_container.h"
#include "custom_sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		using decay = std::remove_pointer_t<std::decay_t<T>>;

		template<typename T>
		struct is_auto_register_type : std::bool_constant<
			std::is_arithmetic_v<T> ||
			is_associative_container<T>::value ||
			is_sequence_container<T>::value>
		{};

		template<typename T>
		struct is_enum_type : std::bool_constant<
			std::is_enum_v<T> && !std::is_convertible_v<T, int>>
		{};

		template<typename T>
		struct is_valid_param : std::bool_constant<
			!std::is_array_v<T> &&
			!std::is_null_pointer_v<T> &&
			!std::is_pointer_v<std::remove_pointer_t<std::decay_t<T>>> &&
			!std::is_void_v<T>>
		{};

		template<typename T>
		struct is_valid_type : std::bool_constant<
			!std::is_array_v<T> &&
			!std::is_const_v<T> &&
			!std::is_null_pointer_v<T> &&
			!std::is_pointer_v<T> &&
			!std::is_reference_v<T> &&
			!std::is_void_v<T> &&
			!std::is_volatile_v<T>>
		{};
	}
}
