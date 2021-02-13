// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		struct factory_data final
		{
			void* (*m_constructor)() { nullptr };
			void* (*m_copy)(void*) { nullptr };
			void (*m_destructor)(void*) { nullptr };
		};
	}
}
