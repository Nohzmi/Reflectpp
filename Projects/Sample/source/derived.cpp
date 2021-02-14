// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "derived.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::class_<Derived>().base<Base>()
	.property("DerivedValue0", &Derived::DerivedValue0)
	.property("DerivedValue1", &Derived::DerivedValue1)
	.property("DerivedValue2", &Derived::DerivedValue2)
	.property("DerivedValue3", &Derived::DerivedValue3)
	.property("DerivedValue4", &Derived::DerivedValue4)
	.property("TestValue", &Derived::TestValue)
	.property("TestValue2", &Derived::TestValue2)
	.property("TestPtrBase", &Derived::TestPtrBase)
	.property("TestPtrDerived", &Derived::TestPtrDerived);
}
