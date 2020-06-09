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

struct Primitives
{
	short value0;
	short int value1;
	signed short value2;
	signed short int value3;
	unsigned short value4;
	unsigned short int value5;
	int value6;
	signed value7;
	signed int value8;
	unsigned value9;
	unsigned int value10;
	long value11;
	long int value12;
	long int value13;
	signed long value14;
	signed long int value15;
	unsigned long value16;
	unsigned long int value17;
	long long value18;
	long long int value19;
	signed long long value20;
	signed long long int value21;
	unsigned long long value22;
	unsigned long long int value23;
	bool value24;
	signed char value25;
	unsigned char value26;
	wchar_t value27;
	char16_t value28;
	char32_t value29;
	float value30;
	double value31;
	long double value32;
};

REGISTRATION
{
	Class<Primitives>("Primitives")
	.field("value0", &Primitives::value0)
	.field("value1", &Primitives::value1)
	.field("value2", &Primitives::value2)
	.field("value3", &Primitives::value3)
	.field("value4", &Primitives::value4)
	.field("value5", &Primitives::value5)
	.field("value6", &Primitives::value6)
	.field("value7", &Primitives::value7)
	.field("value8", &Primitives::value8)
	.field("value9", &Primitives::value9)
	.field("value10", &Primitives::value10)
	.field("value11", &Primitives::value11)
	.field("value12", &Primitives::value12)
	.field("value13", &Primitives::value13)
	.field("value14", &Primitives::value14)
	.field("value15", &Primitives::value15)
	.field("value16", &Primitives::value16)
	.field("value17", &Primitives::value17)
	.field("value18", &Primitives::value18)
	.field("value19", &Primitives::value19)
	.field("value20", &Primitives::value20)
	.field("value21", &Primitives::value21)
	.field("value22", &Primitives::value22)
	.field("value23", &Primitives::value23)
	.field("value24", &Primitives::value24)
	.field("value25", &Primitives::value25)
	.field("value26", &Primitives::value26)
	.field("value27", &Primitives::value27)
	.field("value28", &Primitives::value28)
	.field("value29", &Primitives::value29)
	.field("value30", &Primitives::value30)
	.field("value31", &Primitives::value31)
	.field("value32", &Primitives::value32);
}

int main()
{
	// Reflection test
	//auto test = Type::Get<Test>();
	auto test = Type::Get<Primitives>();

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
