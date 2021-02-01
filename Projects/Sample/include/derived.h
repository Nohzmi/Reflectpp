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
#include <map>
#include <list>
#include <set>

class Derived : public Base
{
	REFLECT(Derived)

public:

	float DerivedValue0;
	Intern DerivedValue1;
	std::vector<const char *> DerivedValue2;
	std::map<char, float> DerivedValue3;
	std::list<float> DerivedValue4;
};
