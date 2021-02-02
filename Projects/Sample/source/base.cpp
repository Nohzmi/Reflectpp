// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "base.h"
#include <registration.h>

float Base::GetValue0() const
{
	return BaseValue0;
}

void Base::SetValue0(float value)
{
	BaseValue0 = value;
}

const Intern& Base::GetValue1() const
{
	return BaseValue1;
}

void Base::SetValue1(const Intern& value)
{
	BaseValue1 = value;
}

REGISTRATION
{
	reflectpp::registration::class_<Base>()
	.property("BaseValue0", &Base::GetValue0, &Base::SetValue0)
	.property("BaseValue1", &Base::GetValue1, &Base::SetValue1);

	/*reflectpp::registration::enumeration<E_Alignment>("E_Alignment")
	.value("AlignLeft", E_Alignment::AlignLeft)
	.value("AlignRight", E_Alignment::AlignRight)
	.value("AlignHCenter", E_Alignment::AlignHCenter)
	.value("AlignJustify", E_Alignment::AlignJustify);*/
}
