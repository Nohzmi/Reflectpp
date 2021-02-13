// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_view_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "custom_associative_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Key>
		REFLECTPP_INLINE auto get_associative_at() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_associative_clear() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto get_associative_equal_range() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto get_associative_erase() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto get_associative_find() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Iterator, typename Key, typename Value>
		REFLECTPP_INLINE auto get_associative_insert() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Iterator, typename Key>
		REFLECTPP_INLINE auto get_associative_insert() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_associative_size() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/associative_view_lambda.inl"
