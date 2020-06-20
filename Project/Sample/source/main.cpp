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
	Intern* tmp3 = new Intern();
	Intern tmp4 = Intern();

	auto& test5 = Type::Get(tmp0);
	auto& test6 = Type::Get(tmp1);
	auto& test7 = Type::Get(&tmp4);

	auto test8 = Type::Cast<Base*>(&tmp4);
	auto test9 = Type::Cast<Derived*>(tmp0);

	auto test10 = Type::Get<Derived>().GetFactory().Construct();
	Type::Get<Derived>().GetFactory().Destroy(test10);
	auto test11 = TypeInfo::Get<Intern>();

	Variant var1 = Variant(tmp0);
	Variant var2 = var1;
	Variant var3 = Variant(tmp3);
	Variant var4 = Variant(&tmp4);

	auto& tmp55 = var1.GetType();
	auto tmp56 = var1.IsType<Base>();
	auto& tmp57 = var1.GetValue<Base>();

	auto other5 = Type::Get<Base>().Create();

	tmp0->SetValue(5.f);
	tmp0->SetValue1(6.0);
	tmp3->InternValue0 = 12.f;
	tmp3->InternValue1 = 13.0;

	auto varssss = Type::Get<Intern>().Create();
	Intern intern;
	intern.InternValue0 = 5363.f;
	intern.InternValue1 = 53634.0;

	for (auto& prop : Type::Get<Intern>().GetProperties())
	{
		//Variant var = prop.GetValue(tmp3);
		Variant var = prop.GetValue(var3);

		if (var.IsType<double>())
			printf("%s is a double : %f\n", prop.GetName(), var.GetValue<double>());
		else if (var.IsType<float>())
			printf("%s is a float : %f\n", prop.GetName(), var.GetValue<float>());
	}

	for (auto& prop : Type::Get<Base>().GetProperties())
	{
		//Variant var = prop.GetValue(tmp3);
		Variant var = prop.GetValue(tmp0);

		if (var.IsType<double>())
			printf("%s is a double : %f\n", prop.GetName(), var.GetValue<double>());
		else if (var.IsType<float>())
			printf("%s is a float : %f\n", prop.GetName(), var.GetValue<float>());
	}

	delete tmp0;
	delete tmp1;
	delete tmp2;
	delete tmp3;

	// Serialization test
	//Test object;
	//Serializer save("test");
	//save.Save(object);

	// Exit point
	printf("\nExit Success!\n\n");

	return EXIT_SUCCESS;
}
