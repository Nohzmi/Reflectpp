// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "derived.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::class_<Derived>().base<Base>()
	.property("DerivedValue0", &Derived::DerivedValue0)
	.property("DerivedValue1", &Derived::DerivedValue1);
}
