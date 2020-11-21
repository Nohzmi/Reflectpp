// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T> template<typename U>
	inline bool range<T>::iterator<U>::operator==(const iterator<U>& rhs) const
	{
		return (m_index == rhs.m_index) && (m_range == rhs.m_range);
	}

	template<typename T> template<typename U>
	inline bool range<T>::iterator<U>::operator!=(const iterator<U>& rhs) const
	{
		return (m_index != rhs.m_index) || (m_range != rhs.m_range);
	}

	template<typename T> template<typename U>
	inline range<T>::iterator<U>& range<T>::iterator<U>::operator++()
	{
		++m_index;
		return *this;
	}

	template<typename T> template<typename U>
	inline U& range<T>::iterator<U>::operator*() const
	{
		return (*m_range)[m_index];
	}

	template<typename T>
	inline T& range<T>::operator[](size_t n) const noexcept
	{
		return *m_vector[n];
	}

	template<typename T>
	inline range<T>::iterator<T> range<T>::begin() const noexcept
	{
		iterator<T> it;
		it.m_index = 0;
		it.m_range = this;

		return it;
	}

	template<typename T>
	inline bool range<T>::empty() const noexcept
	{
		return m_vector.empty();
	}

	template<typename T>
	inline range<T>::iterator<T> range<T>::end() const noexcept
	{
		iterator<T> it;
		it.m_index = size();
		it.m_range = this;

		return it;
	}

	template<typename T>
	inline size_t range<T>::size() const noexcept
	{
		return m_vector.size();
	}
}
