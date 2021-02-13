// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename>
	REFLECTPP_INLINE argument::argument(T&& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ new variant(object) }
	{
	}

	template<typename T>
	REFLECTPP_INLINE bool argument::is_type() const REFLECTPP_NOEXCEPT
	{
		return m_variant != nullptr ? m_variant->is_type<T>() : false;
	}
}
