// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file transform.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "component.h"

class Transform : public Component
{
	REFLECT(Transform)

public:

	float GetX() const { return x; }
	float GetY() const { return y; }
	const float& GetZ() const { return z; }
	void SetX(float value) { x = value; }
	void SetY(float value) { y = value; }
	void SetZ(const float& value) { z = value; }

private:

	float x{ 0.f };
	float y{ 0.f };
	float z{ 0.f };
};
