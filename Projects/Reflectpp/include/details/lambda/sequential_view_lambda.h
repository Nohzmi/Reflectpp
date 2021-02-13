// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequential_view_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "custom_sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_assign() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_assign_impl() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_at() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_at_impl() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_clear() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_erase() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto sequential_view_insert() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_resize() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_size() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto sequential_view_size_impl() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/sequential_view_lambda.inl"
