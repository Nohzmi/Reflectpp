// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "factory.h"

namespace reflectpp
{
	void* factory::construct() const noexcept
	{
		return m_constructor();
	}

	void* factory::copy(void* object) const noexcept
	{
		return m_copy(object);
	}

	void factory::destroy(void* object) const noexcept
	{
		m_destructor(object);
	}

	factory::factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept :
		m_constructor{ constructor },
		m_copy{ copy },
		m_destructor{ destructor }
	{
	}
}
