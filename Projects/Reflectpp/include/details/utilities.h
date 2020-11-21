// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utilities.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

#include "details/structs.h"
#include "details/macros.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		size_t type_id() REFLECTPP_NOEXCEPT;

		template<typename T>
		size_t type_id(T* object) REFLECTPP_NOEXCEPT;

		template<typename T>
		const char* type_name() REFLECTPP_NOEXCEPT;

		template<typename T>
		const char* type_name(T* object) REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/utilities.inl"
