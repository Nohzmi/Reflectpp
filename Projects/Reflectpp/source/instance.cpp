// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "instance.h"

#include "type.h"

namespace reflectpp
{
	type instance::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant.get_type();
	}
}
