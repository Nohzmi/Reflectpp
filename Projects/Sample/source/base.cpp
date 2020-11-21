// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "base.h"
#include <registration.h>

float Base::GetValue() const
{
	return BaseValue0;
}

void Base::SetValue(float value)
{
	BaseValue0 = value;
}

const double& Base::GetValue1() const
{
	return BaseValue1;
}

void Base::SetValue1(const double& value)
{
	BaseValue1 = value;
}

const ZTest& Base::GetValue2() const
{
	return value;
}

void Base::SetValue2(const ZTest& _value)
{
	value = _value;
}

REGISTRATION
{
	reflectpp::registration::class_<Base>()
	.property("BaseValue0", &Base::GetValue, &Base::SetValue)
	.property("BaseValue1", &Base::GetValue1, &Base::SetValue1)
	//property("value", &Base::value);
	.property("value", &Base::GetValue2, &Base::SetValue2);
}
