// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Derived.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <Register.h>
#include "Base.h"

class Derived : public Base
{
	REFLECT()

public:

	float DerivedValue0;
	double DerivedValue1;
};
