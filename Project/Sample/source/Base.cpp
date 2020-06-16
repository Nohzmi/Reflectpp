// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Base.h"
#include <Type.h>

REGISTRATION
{
	Type::class_<Base>("Base")
	.property("BaseValue0", &Base::BaseValue0)
	.property("BaseValue1", &Base::BaseValue1);
}
