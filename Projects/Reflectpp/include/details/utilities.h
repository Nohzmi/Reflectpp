// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utilities.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

#include "details/structs.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		size_t type_id() noexcept;

		template<typename T>
		size_t type_id(T* object) noexcept;

		template<typename T>
		const char* type_name() noexcept;

		template<typename T>
		const char* type_name(T* object) noexcept;
	}
}

#include "details/inline/utilities.inl"
