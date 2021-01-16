// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "argument.h"

#include "type.h"

namespace reflectpp
{
	type argument::get_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant->get_type();
	}
}
