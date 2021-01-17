// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct factory_data final
		{
			Constructor m_constructor{ nullptr };
			Copy m_copy{ nullptr };
			Destructor m_destructor{ nullptr };
		};
	}
}
