// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file base.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <register.h>
#include "intern.h"

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
