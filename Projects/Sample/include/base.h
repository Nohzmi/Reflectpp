// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file base.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <register.h>
#include "ztest.h"

class Base
{
	REFLECT(Base)

public:

	float GetValue() const;
	void SetValue(float value);

	const double& GetValue1() const;
	void SetValue1(const double& value);

	const ZTest& GetValue2() const;
	void SetValue2(const ZTest& value);

private:

	float BaseValue0;
	double BaseValue1;

public:

	ZTest value;
};
