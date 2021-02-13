// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utility_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

namespace reflectpp
{
	namespace details
	{
		struct utility_data final
		{
			std::vector<bool> m_can_convert_from;
			std::vector<bool> m_can_convert_to;
			bool (*m_compare)(void*, void*) { nullptr };
			std::vector<void* (*)(void*)> m_convert_from;
			std::vector<void* (*)(void*)> m_convert_to;
		};
	}
}
