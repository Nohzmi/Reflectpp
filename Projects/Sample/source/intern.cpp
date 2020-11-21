// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "intern.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::class_<Intern>()
	.property("InternValue0", &Intern::InternValue0)
	.property("InternValue1", &Intern::InternValue1);
}
