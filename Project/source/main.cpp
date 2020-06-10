// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cstdio>
#include "Type.h"
#include "Register.h"

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

struct V { REFLECT() };
struct A : V { REFLECT() };
struct B : V { REFLECT() };
struct D : A, B { REFLECT() };

REGISTRATION
{
	Class<V>("V");

Class<A>("A")
.base<V>();

Class<B>("B")
.base<V>();

Class<D>("D")
.base<A>()
.base<B>();
}

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
	D d; // the most derived object
	A* a = &d; // upcast, dynamic_cast may be used, but unnecessary
	D* new_d = Type::Cast<D*>(a); // downcast
	B* new_b = Type::Cast<B*>(a); // sidecast

	// Reflection test
	auto test0 = Type::Get<Test>();
	auto test2 = Type::Get<Test>()->GetBaseTypes();
	auto test3 = Type::Get<Test>()->GetDerivedTypes();
	auto test4 = Type::Get<Test>()->GetFields();

	BaseTest* tmp0 = new BaseTest();
	BaseTest* tmp1 = new Test();
	auto test5 = Type::Get(tmp0);
	auto test6 = Type::Get(tmp1);

	auto test7 = Type::Cast<Intern*>(tmp0);

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
