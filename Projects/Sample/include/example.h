// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file example.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "component.h"

enum class Enum : int
{
	None = 0,
	First = 1,
	Second = 2,
	Third = 3
};

class Example : public Component
{
	REFLECT(Example)

public:

	bool BoolValue{ false };
	float FloatValue{ 0.f };
	int IntValue{ 0 };
	Enum EnumValue{ Enum::None };
	std::string StringValue{ "text" };
};
