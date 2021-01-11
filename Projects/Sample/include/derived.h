// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file derived.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <register.h>
#include "base.h"

class Derived : public Base
{
	REFLECT(Derived)

public:

	float DerivedValue0;
};
