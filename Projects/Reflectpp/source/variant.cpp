// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "variant.h"

#include "type.h"
#include "variant_sequencial_view.h"

namespace reflectpp
{
	variant_sequencial_view variant::create_sequential_view() const REFLECTPP_NOEXCEPT
	{
		return is_sequential_container() ? variant_sequencial_view({ false, m_data.m_type, m_data.m_value }) : variant_sequencial_view();
	}

	type variant::get_type() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? type(m_data.m_type) : type();
	}
}
