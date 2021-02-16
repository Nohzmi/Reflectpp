// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "example.h"
#include <registration.h>

REGISTRATION
{
	reflectpp::registration::enumeration<Enum>("EnumExample")
	.value("None", Enum::None)
	.value("First", Enum::First)
	.value("Second", Enum::Second)
	.value("Third", Enum::Third);

	reflectpp::registration::class_<Example>().base<Component>()
	.property("BoolValue", &Example::BoolValue)
	.property("FloatValue", &Example::FloatValue)
	.property("IntValue", &Example::IntValue)
	.property("EnumValue", &Example::EnumValue)
	.property("StringValue", &Example::StringValue);
}

