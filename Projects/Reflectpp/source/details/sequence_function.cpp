// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/sequence_function.h"

namespace reflectpp
{
	namespace details
	{
		void sequence_function::clear(void* container) const REFLECTPP_NOEXCEPT
		{
			return m_clear(container);
		}

		void sequence_function::erase(void* container, size_t index) const REFLECTPP_NOEXCEPT
		{
			m_erase(container, index);
		}

		void* sequence_function::get(void* container, size_t index) const REFLECTPP_NOEXCEPT
		{
			return m_get(container, index);
		}

		void sequence_function::insert(void* container, size_t index, void* value) const REFLECTPP_NOEXCEPT
		{
			m_insert(container, index, value);
		}

		void sequence_function::resize(void* container, size_t size) const REFLECTPP_NOEXCEPT
		{
			m_resize(container, size);
		}

		void sequence_function::set(void* container, size_t index, void* value) const REFLECTPP_NOEXCEPT
		{
			return m_set(container, index, value);
		}

		size_t sequence_function::size(void* container) const REFLECTPP_NOEXCEPT
		{
			return m_size(container);
		}

		sequence_function::sequence_function(ClearT clear, EraseT erase, GetT get, InsertT insert, ResizeT resize, SetT set, SizeT size) REFLECTPP_NOEXCEPT :
			m_clear{ clear },
			m_erase{ erase },
			m_get{ get },
			m_insert{ insert },
			m_resize{ resize },
			m_set{ set },
			m_size{ size }
		{
		}
	}
}
