// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <Type.h>
#include <vld.h>

#include "Base.h"
#include "Derived.h"
#include "Intern.h"

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
	auto& other0 = Type::Get<Base>();
	auto& other1 = Type::Get<Intern>();

	for (auto& it : Type::Get<Derived>().GetBaseTypes())
		printf("%s\n", it.GetName());

	Base* tmp0 = new Base();
	Base* tmp1 = new Derived();
	int* tmp2 = new int();

	auto& test5 = Type::Get(tmp0);
	auto& test6 = Type::Get(tmp1);
	auto& test7 = Type::Get(tmp2);

	auto test8 = Type::Cast<Base*>(tmp0);
	auto test9 = Type::Cast<Derived*>(tmp0);

	auto test10 = Type::Get<Derived>().GetFactory().Construct();
	Type::Get<Derived>().GetFactory().Destroy(test10);
	auto test11 = TypeInfo::Get<Intern>();

	Variant var1 = Variant(tmp0);
	Variant var2 = var1;
	Variant var3;

	auto& tmp55 = var1.GetType();
	auto tmp56 = var1.IsType<Base>();
	auto& tmp57 = var1.GetValue<Base>();

	delete tmp0;
	delete tmp1;
	delete tmp2;

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	// Exit point
	printf("\nExit Success!\n\n");

	return EXIT_SUCCESS;
}
