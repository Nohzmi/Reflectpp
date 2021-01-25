// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file derived.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <register.h>
#include "base.h"

#include <array>
#include <vector>

class Derived : public Base
{
	REFLECT(Derived)

public:

	std::vector<float> DerivedValue0;
	float DerivedValue1;
	Intern DerivedValue2;
};
