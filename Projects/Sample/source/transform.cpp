// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "transform.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::class_<Transform>().base<Component>()
	.property("X", &Transform::GetX, &Transform::SetX)
	.property("Y", &Transform::GetY, &Transform::SetY)
	.property("Z", &Transform::GetZ, &Transform::SetZ);
}
