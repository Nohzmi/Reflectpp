// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "type.h"

/**
* @addtogroup Reflectpp
* @{
*/
namespace reflectpp
{
	namespace details
	{
		class sequence_function;

		class REFLECTPP_API sequence_type final : public type
		{
			friend details::registry;

		public:

			sequence_type() = delete;
			~sequence_type() = default;
			sequence_type(const sequence_type&) = delete;
			sequence_type(sequence_type&&) REFLECTPP_NOEXCEPT = default;
			sequence_type& operator=(const sequence_type&) = delete;
			sequence_type& operator=(sequence_type&&) REFLECTPP_NOEXCEPT = default;

			virtual bool is_sequential_container() const REFLECTPP_NOEXCEPT override;
			type* get_data_type() const REFLECTPP_NOEXCEPT;
			sequence_function* get_sequence_function() const REFLECTPP_NOEXCEPT;

		private:

			sequence_type(type* data_type, factory* _factory, sequence_function* _sequence_function, size_t size, type_info* _type_info) REFLECTPP_NOEXCEPT;

			type* m_data_type;
			sequence_function* m_sequence_function;
		};
	}
}

/**
* @}
*/
