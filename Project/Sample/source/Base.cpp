// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Base.h"
#include <Type.h>

REGISTRATION
{
	Class<Base>("Base")
	.field("BaseValue0", &Base::BaseValue0)
	.field("BaseValue1", &Base::BaseValue1);
}
