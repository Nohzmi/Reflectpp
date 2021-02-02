// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequenctial_view_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"
#include "custom_sequence_container.hpp"

namespace reflectpp
{
	namespace details
	{
		template<typename Class, typename Value>
		REFLECTPP_INLINE auto get_sequence_assign() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto get_sequence_assign_impl() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_at() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_at_impl() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_clear() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_erase() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto get_sequence_insert() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_resize() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_size() REFLECTPP_NOEXCEPT;

		template<typename Class>
		REFLECTPP_INLINE auto get_sequence_size_impl() REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/sequential_view_lambda.inl"
