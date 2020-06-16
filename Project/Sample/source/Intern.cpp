// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Intern.h"
#include <Type.h>

REGISTRATION
{
	Class<Intern>("Intern")
	.field("InternValue0", &Intern::InternValue0)
	.field("InternValue1", &Intern::InternValue1);
}
