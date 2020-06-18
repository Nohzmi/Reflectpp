// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <Type.h>
#include <vld.h>

#include "Base.h"
#include "Derived.h"
#include "Intern.h"

struct Not {};

struct A { virtual ~A() {} };
struct B { virtual ~B() {} };
struct C : public A, B { virtual ~C() {} };

int main()
{
	// Entry point
	printf("\nHello World!\n\n");

	// Reflection test
	auto& test = Type::Get<Derived>();
	auto& test0 = Type::Get<Derived>();
	auto& test2 = Type::Get<Derived>().GetBaseTypes();
	auto& test3 = Type::Get<Derived>().GetDerivedTypes();
	auto& test4 = Type::Get<Derived>().GetProperties();
	auto& test45 = Type::Get<Base>();
	auto& test46 = Type::Get<Intern>();

	Base* tmp0 = new Base();
	Base* tmp1 = new Derived();
	int* tmp2 = new int();

	auto& test5 = Type::Get(tmp0);
	auto& test6 = Type::Get(tmp1);
	auto& test7 = Type::Get(tmp2);

	auto test8 = Type::Cast<Base*>(tmp0);
	auto test754 = Type::Cast<Derived*>(tmp0);

	auto test11 = Type::Get<Derived>().GetFactory().Construct();
	Type::Get<Derived>().GetFactory().Destroy(test11);
	auto test12 = TypeInfo::Get<Intern>();
	auto test13 = TypeInfo::Get<Not>();
	auto test14 = Factory::Get<Not>();

	delete tmp0;
	delete tmp1;
	delete tmp2;

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
