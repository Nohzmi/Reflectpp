// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file range.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

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
			iterator(iterator&&) noexcept = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) noexcept = default;

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
		range(range&&) noexcept = default;
		range& operator=(const range&) = delete;
		range& operator=(range&&) noexcept = default;

		T& operator[] (size_t n) const noexcept;
		iterator<T> begin() const noexcept;
		bool empty() const noexcept;
		iterator<T> end() const noexcept;
		size_t size() const noexcept;

	private:

		std::vector<T*> m_vector;
	};
}

#include "details/inline/range.inl"

/**
* @}
*/
