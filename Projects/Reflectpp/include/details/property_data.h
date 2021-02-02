// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>

#include "details/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct property_data final
		{
			type_data* m_declaring_type{ nullptr };
			std::function<void* (void*, bool&)> m_getter{ nullptr };
			size_t m_id{ 0 };
			const char* m_name{ "" };
			std::function<void (void*, void*)> m_setter{ nullptr };
			size_t m_specifiers{ 0 };
			type_data* m_type{ nullptr };
		};
	}
}
