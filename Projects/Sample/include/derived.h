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
#include <unordered_map>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <deque>

class Derived : public Base
{
	REFLECT(Derived)

public:

	float DerivedValue0;
	Intern DerivedValue1;
	std::vector<float> DerivedValue2;
	std::map<char, float> DerivedValue3;
	std::set<char> DerivedValue4;
	std::wstring TestValue = L"sometext";
	std::vector<std::vector<int>> TestValue2 = { {5, 6}, {12,13} };
	std::unique_ptr<Base> TestPtrBase;
	std::unique_ptr<Base> TestPtrDerived;
	E_Alignment EnumValue = E_Alignment::AlignJustify;
};
