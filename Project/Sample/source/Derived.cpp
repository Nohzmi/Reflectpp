// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Derived.h"
#include <Type.h>

REGISTRATION
{
	Class<Derived>("Derived")
	.base<Base>()
	.field("DerivedValue0", &Derived::DerivedValue0)
	.field("DerivedValue1", &Derived::DerivedValue1);
}
