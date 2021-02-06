// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utility_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		struct utility_data final
		{
			bool m_can_convert_to_bool { false };
			bool m_can_convert_to_char{ false };
			bool m_can_convert_to_double { false };
			bool m_can_convert_to_float { false };
			bool m_can_convert_to_int { false };
			bool m_can_convert_to_int8 { false };
			bool m_can_convert_to_int16 { false };
			bool m_can_convert_to_int32 { false };
			bool m_can_convert_to_int64 { false };
			bool m_can_convert_to_uint8 { false };
			bool m_can_convert_to_uint16 { false };
			bool m_can_convert_to_uint32 { false };
			bool m_can_convert_to_uint64 { false };
			bool (*m_compare)(void*, void*) { nullptr };
			void* (*m_convert_to_bool)(void*) { nullptr };
			void* (*m_convert_to_char)(void*) { nullptr };
			void* (*m_convert_to_double)(void*) { nullptr };
			void* (*m_convert_to_float)(void*) { nullptr };
			void* (*m_convert_to_int)(void*) { nullptr };
			void* (*m_convert_to_int8)(void*) { nullptr };
			void* (*m_convert_to_int16)(void*) { nullptr };
			void* (*m_convert_to_int32)(void*) { nullptr };
			void* (*m_convert_to_int64)(void*) { nullptr };
			void* (*m_convert_to_uint8)(void*) { nullptr };
			void* (*m_convert_to_uint16)(void*) { nullptr };
			void* (*m_convert_to_uint32)(void*) { nullptr };
			void* (*m_convert_to_uint64)(void*) { nullptr };
		};
	}
}
