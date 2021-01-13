// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/sequence_type.h"

namespace reflectpp
{
	namespace details
	{
		sequence_type::sequence_type(type* data_type, factory* _factory, sequence_function* _sequence_function, size_t size, type_info* _type_info) REFLECTPP_NOEXCEPT :
			type(_factory, size, _type_info),
			m_data_type{ data_type },
			m_sequence_function{ _sequence_function }
		{
		}

		bool sequence_type::is_sequential_container() const REFLECTPP_NOEXCEPT
		{
			return true;
		}

		type* reflectpp::details::sequence_type::get_data_type() const REFLECTPP_NOEXCEPT
		{
			return m_data_type;
		}

		sequence_function* sequence_type::get_sequence_function() const REFLECTPP_NOEXCEPT
		{
			return m_sequence_function;
		}
	}
}
