// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "ztest.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::class_<ZTest>()
	.property("zvalue0", &ZTest::zvalue0)
	.property("zvalue1", &ZTest::zvalue1);
}
