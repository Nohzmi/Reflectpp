// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "factory.h"

namespace reflectpp
{
	void* factory::construct() const REFLECTPP_NOEXCEPT
	{
		return m_constructor();
	}

	void* factory::copy(void* object) const REFLECTPP_NOEXCEPT
	{
		return m_copy(object);
	}

	void factory::destroy(void* object) const REFLECTPP_NOEXCEPT
	{
		m_destructor(object);
	}

	factory::factory(ConstructorT constructor, CopyT copy, DestructorT destructor) REFLECTPP_NOEXCEPT :
		m_constructor{ constructor },
		m_copy{ copy },
		m_destructor{ destructor }
	{
	}
}
