// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file base.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <register.h>
#include "intern.h"

enum class E_Alignment
{
	AlignLeft = 0x0001,
	AlignRight = 0x0002,
	AlignHCenter = 0x0004,
	AlignJustify = 0x0008
};

class Base
{
	REFLECT(Base)

public:

	float GetValue0() const;
	void SetValue0(float value);

	const Intern& GetValue1() const;
	void SetValue1(const Intern& value);

private:

	float BaseValue0;
	Intern BaseValue1;
};
