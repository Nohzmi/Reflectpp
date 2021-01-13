// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_function.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"

/**
* @addtogroup Reflectpp
* @{
*/
namespace reflectpp
{
	namespace details
	{
		class REFLECTPP_API sequence_function final
		{
			friend details::registry;

			using ClearT = void (*)(void*);
			using EraseT = void (*)(void*, size_t);
			using GetT = void* (*)(void*, size_t);
			using InsertT = void (*)(void*, size_t, void*);
			using ResizeT = void (*)(void*, size_t);
			using SetT = void (*)(void*, size_t, void*);
			using SizeT = size_t (*)(void*);

		public:

			sequence_function() = delete;
			~sequence_function() = default;
			sequence_function(const sequence_function&) = delete;
			sequence_function(sequence_function&&) REFLECTPP_NOEXCEPT = delete;
			sequence_function& operator=(const sequence_function&) = delete;
			sequence_function& operator=(sequence_function&&) REFLECTPP_NOEXCEPT = delete;

			void clear(void* container) const REFLECTPP_NOEXCEPT;
			void erase(void* container, size_t index) const REFLECTPP_NOEXCEPT;
			void* get(void* container, size_t index) const REFLECTPP_NOEXCEPT;
			void insert(void* container, size_t index, void* value) const REFLECTPP_NOEXCEPT;
			void resize(void* container, size_t size) const REFLECTPP_NOEXCEPT;
			void set(void* container, size_t index, void* value) const REFLECTPP_NOEXCEPT;
			size_t size(void* container) const REFLECTPP_NOEXCEPT;

		private:

			sequence_function(ClearT clear, EraseT erase, GetT get, InsertT insert, ResizeT resize, SetT set, SizeT size) REFLECTPP_NOEXCEPT;

			ClearT m_clear;
			EraseT m_erase;
			GetT m_get;
			InsertT m_insert;
			ResizeT m_resize;
			SetT m_set;
			SizeT m_size;
		};
	}
}

/**
* @}
*/
