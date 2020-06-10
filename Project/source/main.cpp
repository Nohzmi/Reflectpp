// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cstdio>
#include "Type.h"

struct Intern
{
	char internCharValue = 1;
	short internShortValue = 2;
};

REGISTRATION
{
	Class<Intern>("Intern")
	.field("internCharValue", &Intern::internCharValue)
	.field("internShortValue", &Intern::internShortValue);
}

struct BaseTest
{
	float baseFloatValue = 5.f;
	double baseDoubleValue = 6.f;
};

REGISTRATION
{
	Class<BaseTest>("BaseTest")
	.field("baseFloatValue", &BaseTest::baseFloatValue)
	.field("baseDoubleValue", &BaseTest::baseDoubleValue);
}

struct Test : public BaseTest
{
	Intern interValue;
	int IntValue = 3;
	long LongValue = 4;
};

REGISTRATION
{
	Class<Test>("Test")
	.base<BaseTest>()
	.field("interValue", &Test::interValue)
	.field("IntValue", &Test::IntValue)
	.field("LongValue", &Test::LongValue);
}

int main()
{
	// Reflection test
	auto test0 = Type::Get<Test>();
	auto test2 = Type::Get<Test>()->GetBaseTypes();
	auto test3 = Type::Get<Test>()->GetDerivedTypes();
	auto test4 = Type::Get<Test>()->GetFields();

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
