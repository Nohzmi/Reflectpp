// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename>
	REFLECTPP_INLINE instance::instance(T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ new variant(object) }
	{
	}

	template<typename T>
	REFLECTPP_INLINE T* instance::try_convert() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr && m_variant->convert<T>() ? m_variant->m_data.m_value : nullptr;
	}
}
