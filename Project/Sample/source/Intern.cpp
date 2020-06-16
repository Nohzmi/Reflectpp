// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Intern.h"
#include <Type.h>

REGISTRATION
{
	Type::class_<Intern>("Intern")
	.property("InternValue0", &Intern::InternValue0)
	.property("InternValue1", &Intern::InternValue1);
}
