// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cstdio>
#include "Type.h"

struct Intern
{
	int internValue = 8;
};

REGISTRATION
{
	Class<Intern>("Intern")
	.field("internValue", &Intern::internValue);
}

struct BaseTest
{
	int baseValue = 4;
};

REGISTRATION
{
	Class<BaseTest>("BaseTest")
	.field("baseValue", &BaseTest::baseValue);
}

struct Test : public BaseTest
{
	//Test(int t) : value0{ t } {}

	int value0 = 4;
	float value1 = 5.08f;

	Intern value2;
};

REGISTRATION
{
	Class<Test>("Test")
	.base<BaseTest>()
	.field("value0", &Test::value0)
	.field("value1", &Test::value1)
	.field("value2", &Test::value2);
}

int main()
{
	// Reflection test
	//auto test = Type::Get<int>();
	auto test1 = Type::Get<Test>();

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
