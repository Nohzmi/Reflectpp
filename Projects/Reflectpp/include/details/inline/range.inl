// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T> template<typename U>
	REFLECTPP_INLINE bool range<T>::iterator<U>::operator==(const iterator<U>& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index == rhs.m_index) && (m_range == rhs.m_range);
	}

	template<typename T> template<typename U>
	REFLECTPP_INLINE bool range<T>::iterator<U>::operator!=(const iterator<U>& rhs) const REFLECTPP_NOEXCEPT
	{
		return (m_index != rhs.m_index) || (m_range != rhs.m_range);
	}

	template<typename T> template<typename U>
	REFLECTPP_INLINE range<T>::iterator<U>& range<T>::iterator<U>::operator++() REFLECTPP_NOEXCEPT
	{
		++m_index;
		return *this;
	}

	template<typename T> template<typename U>
	REFLECTPP_INLINE U& range<T>::iterator<U>::operator*() const REFLECTPP_NOEXCEPT
	{
		return (*m_range)[m_index];
	}

	template<typename T>
	REFLECTPP_INLINE T& range<T>::operator[](size_t n) const REFLECTPP_NOEXCEPT
	{
		return *m_vector[n];
	}

	template<typename T>
	REFLECTPP_INLINE range<T>::iterator<T> range<T>::begin() const REFLECTPP_NOEXCEPT
	{
		iterator<T> it;
		it.m_index = 0;
		it.m_range = this;

		return it;
	}

	template<typename T>
	REFLECTPP_INLINE bool range<T>::empty() const REFLECTPP_NOEXCEPT
	{
		return m_vector.empty();
	}

	template<typename T>
	REFLECTPP_INLINE range<T>::iterator<T> range<T>::end() const REFLECTPP_NOEXCEPT
	{
		iterator<T> it;
		it.m_index = size();
		it.m_range = this;

		return it;
	}

	template<typename T>
	REFLECTPP_INLINE size_t range<T>::size() const REFLECTPP_NOEXCEPT
	{
		return m_vector.size();
	}
}
