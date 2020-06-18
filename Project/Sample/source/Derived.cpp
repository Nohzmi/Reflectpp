// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Derived.h"
#include <Type.h>

REGISTRATION
{
	Registration::class_<Derived>().base<Base>()
	.property("DerivedValue0", &Derived::DerivedValue0)
	.property("DerivedValue1", &Derived::DerivedValue1);
}
