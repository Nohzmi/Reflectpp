// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE argument::~argument()
	{
		if (m_is_owner && m_variant != nullptr)
		{
			delete m_variant;
			m_variant = nullptr;
		}
	}

	REFLECTPP_INLINE argument::argument(const argument& copy)
	{
		*this = copy;
	}

	REFLECTPP_INLINE argument& argument::operator=(const argument& copy)
	{
		m_variant = copy.m_variant;
		return *this;
	}
	
	REFLECTPP_INLINE argument::argument(variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ &var }
	{
	}

	REFLECTPP_INLINE argument::argument(const variant& var) REFLECTPP_NOEXCEPT :
		m_is_owner{ false },
		m_variant{ const_cast<variant*>(&var) }
	{
	}

	template<typename T, typename U>
	REFLECTPP_INLINE argument::argument(T&& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ new variant(object) }
	{
	}

	template<typename T>
	REFLECTPP_INLINE T& argument::get_value() const REFLECTPP_NOEXCEPT
	{
		return m_variant->get_value<T>();

	}

	template<typename T>
	REFLECTPP_INLINE bool argument::is_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant->is_type<T>();
	}
}
