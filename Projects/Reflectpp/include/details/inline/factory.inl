// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	REFLECTPP_INLINE factory::factory(details::factory_data* data) REFLECTPP_NOEXCEPT :
		m_data{ data }
	{
	}

	REFLECTPP_INLINE factory::operator bool() const REFLECTPP_NOEXCEPT
	{
		return is_valid();
	}

	REFLECTPP_INLINE void* factory::construct() const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_constructor() : nullptr;
	}

	REFLECTPP_INLINE void* factory::copy(void* object) const REFLECTPP_NOEXCEPT
	{
		return is_valid() ? m_data->m_copy(object) : nullptr;
	}

	REFLECTPP_INLINE void factory::destroy(void* object) const REFLECTPP_NOEXCEPT
	{
		if (is_valid())
			m_data->m_destructor(object);
	}

	template<typename T>
	REFLECTPP_INLINE factory factory::get() REFLECTPP_NOEXCEPT
	{
		return factory(details::registry::get_instance().get_factory<T>());
	}

	REFLECTPP_INLINE bool factory::is_valid() const REFLECTPP_NOEXCEPT
	{
		return m_data != nullptr;
	}
}
