// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cstdio>
#include "Type.h"
#include "Register.h"

class Intern
{
	REFLECT();

public:
	char internCharValue = 1;
	short internShortValue = 2;
};

REGISTRATION
{
	Class<Intern>("Intern")
	.field("internCharValue", &Intern::internCharValue)
	.field("internShortValue", &Intern::internShortValue);
}

class BaseTest
{
	REFLECT();

public:

	float baseFloatValue = 5.f;
	double baseDoubleValue = 6.f;
};

REGISTRATION
{
	Class<BaseTest>("BaseTest")
	.field("baseFloatValue", &BaseTest::baseFloatValue)
	.field("baseDoubleValue", &BaseTest::baseDoubleValue);
}

class Test : public BaseTest
{
	REFLECT();

public:

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
	// Entry point
	printf("Hello World!\n");

	// Reflection test
	auto test = Type::Get<Test>();
	auto test0 = Type::Get<Test>();
	auto test2 = Type::Get<Test>()->GetBaseTypes();
	auto test3 = Type::Get<Test>()->GetDerivedTypes();
	auto test4 = Type::Get<Test>()->GetFields();

	BaseTest* tmp0 = new BaseTest();
	const BaseTest* tmp1 = new Test();
	int* tmp2 = new int();

	auto test5 = Type::Get(tmp0);
	auto test6 = Type::Get(tmp1);
	auto test7 = Type::Get(tmp2);

	auto test8 = Type::Cast<Intern*>(tmp0);
	auto test9 = Type::Cast<Test*>(tmp0);

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
