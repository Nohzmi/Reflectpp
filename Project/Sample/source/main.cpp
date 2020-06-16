// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <cstdio>
#include <Type.h>

#include "Base.h"
#include "Derived.h"
#include "Intern.h"

int main()
{
	// Entry point
	printf("Hello World!\n");

	// Reflection test
	auto test = Type::Get<Derived>();
	auto test0 = Type::Get<Derived>();
	auto test2 = Type::Get<Derived>()->GetBaseTypes();
	auto test3 = Type::Get<Derived>()->GetDerivedTypes();
	auto test4 = Type::Get<Derived>()->GetProperties();

	Base* tmp0 = new Base();
	Base* tmp1 = new Derived();
	int* tmp2 = new int();

	auto test5 = Type::Get(tmp0);
	auto test6 = Type::Get(tmp1);
	auto test7 = Type::Get(tmp2);

	auto test8 = Type::Cast<Base*>(tmp0);
	auto test9 = Type::Cast<Derived*>(tmp0);
	auto test10 = dynamic_cast<Derived*>(tmp0);

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	return EXIT_SUCCESS;
}
