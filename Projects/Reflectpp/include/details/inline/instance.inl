// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	REFLECTPP_INLINE instance::instance(T& object) REFLECTPP_NOEXCEPT :
		m_is_owner{ true },
		m_variant{ new variant(object) }
	{
	}
}
