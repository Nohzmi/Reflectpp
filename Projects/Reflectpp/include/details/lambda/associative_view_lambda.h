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
		REFLECTPP_INLINE auto associative_view_at() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto associative_view_clear() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_equal_range() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_erase() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Key>
		REFLECTPP_INLINE auto associative_view_find() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Iterator, typename Key, typename Value>
		REFLECTPP_INLINE auto associative_view_insert() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Iterator, typename Key>
		REFLECTPP_INLINE auto associative_view_insert() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto associative_view_size() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/associative_view_lambda.inl"
