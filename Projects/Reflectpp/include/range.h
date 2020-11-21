// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file range.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

#include "details/macros.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	namespace details
	{
		class registry;
	}

	template<typename T>
	class range final
	{
		friend details::registry;

	public:

		template<typename T>
		class iterator
		{
			friend range<T>;

		public:

			~iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) REFLECTPP_NOEXCEPT = default;

			bool operator==(const iterator<T>& rhs) const;
			bool operator!=(const iterator<T>& rhs) const;
			iterator<T>& operator++();
			T& operator*() const;

		private:

			iterator() = default;

			size_t m_index;
			const range<T>* m_range;
		};

		range() = default;
		~range() = default;
		range(const range&) = delete;
		range(range&&) REFLECTPP_NOEXCEPT = default;
		range& operator=(const range&) = delete;
		range& operator=(range&&) REFLECTPP_NOEXCEPT = default;

		T& operator[] (size_t n) const REFLECTPP_NOEXCEPT;
		iterator<T> begin() const REFLECTPP_NOEXCEPT;
		bool empty() const REFLECTPP_NOEXCEPT;
		iterator<T> end() const REFLECTPP_NOEXCEPT;
		size_t size() const REFLECTPP_NOEXCEPT;

	private:

		std::vector<T*> m_vector;
	};
}

#include "details/inline/range.inl"

/**
* @}
*/
