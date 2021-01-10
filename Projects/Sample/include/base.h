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

	const double* GetValue3() const;
	void SetValue3(const double* value);

	volatile double* GetValue4() const;
	void SetValue4(volatile double* value);

public:

	float BaseValue0;
	double BaseValue1;
	double BaseValue3;
	double BaseValue4;

public:

	ZTest value;
};
