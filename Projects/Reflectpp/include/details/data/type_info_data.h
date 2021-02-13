// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_info_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		struct type_info_data final
		{
			size_t m_id{ 0 };
			const char* m_name{ "" };
		};
	}
}
