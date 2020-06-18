// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <vld.h>//////////////////////////////////////////////
#include <cstdio>
#include <Type.h>

#include "Base.h"
#include "Derived.h"
#include "Intern.h"

struct Not {};

int main()
{
	// Entry point
	printf("\nHello World!\n\n");

	// Reflection test
	auto test = Type::Get<Derived>();
	auto test0 = Type::Get<Derived>();
	auto test2 = Type::Get<Derived>()->GetBaseTypes();
	auto test3 = Type::Get<Derived>()->GetDerivedTypes();
	auto test4 = Type::Get<Derived>()->GetProperties();
	auto test45 = Type::Get<Base>();

	Base* tmp0 = new Base();
	Base* tmp1 = new Derived();
	int* tmp2 = new int();

	auto test5 = Type::Get(tmp0);
	auto test6 = Type::Get(tmp1);
	auto test7 = Type::Get(tmp2);

	//auto test8 = Type::Cast<Base*>(tmp0);
	//auto test9 = Type::Cast<Derived*>(tmp0);
	auto test10 = dynamic_cast<Derived*>(tmp0);

	auto test11 = Type::Get<Derived>()->GetFactory().Construct();
	Type::Get<Derived>()->GetFactory().Destroy(test11);
	auto test12 = TypeInfo::Get<Intern>();

	delete tmp0;
	delete tmp1;
	delete tmp2;

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
