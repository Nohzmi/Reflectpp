// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE instance::~instance()
	{
		if (m_is_owner && m_variant != nullptr)
		{
			delete m_variant;
			m_variant = nullptr;
		}
	}

	REFLECTPP_INLINE instance::instance(const instance& copy)
	{
		*this = copy;
	}

	REFLECTPP_INLINE instance& instance::operator=(const instance& copy)
	{
		m_variant = copy.m_variant;
		return *this;
	}

	REFLECTPP_INLINE instance::instance(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ const_cast<variant*>(&var) }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE instance::instance(T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ new variant(object) }
	{
	}

	REFLECTPP_INLINE instance::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	REFLECTPP_INLINE bool instance::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_variant->is_valid();
	}
}
