// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <iostream>
#include <type.h>
#include <factory.h>
#include <type_info.h>
#include <variant.h>
#include <property.h>
#include <serializer.h>
#include <instance.h>
#include <vld/vld.h>

#include "intern.h"
#include "base.h"
#include "derived.h"

using namespace reflectpp;

enum class Testjh
{
	E_TEMP = 0
};


int main()
{
	// Entry point
	printf("\nHello World!\n\n");

	//std::cout << details::type_name(type::get<Derived>()) << std::endl;
	//std::cout << details::type_name(&type::get<Derived>()) << std::endl;

	//auto testdsfsw = factory::get<volatile Base>();
	//auto kjdhflks = testdsfsw.construct();

	int val = 5;
	int* ptr = &val;
	int* ptrnnull = nullptr;
	int** ptr2 = &ptr;

	Base* base = new Base();
	Base* basenull = nullptr;
	delete base;

	/*std::cout << details::registry::get_instance().get_type(5)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(val)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(ptr)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(*ptr)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(&val)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(ptrnnull)->get_name() << std::endl;
	std::cout << details::registry::get_instance().get_type(ptr2)->get_name() << std::endl;*/

	/*int val = 5;
	int* ptr = &val;
	int* ptrnnull = nullptr;
	int** ptr2 = &ptr;*/

	/*Base val = Base();
	Base* ptr = &val;
	Base* ptrnnull = nullptr;
	Base** ptr2 = &ptr;

	std::cout << type::get(Base()).get_name() << std::endl;
	std::cout << type::get(val).get_name() << std::endl;
	std::cout << type::get(ptr).get_name() << std::endl;
	std::cout << type::get(*ptr).get_name() << std::endl;
	std::cout << type::get(&val).get_name() << std::endl;
	std::cout << type::get(ptrnnull).get_name() << std::endl;
	std::cout << type::get(ptr2).get_name() << std::endl;*/


	//return 0;

	// Reflection test
	auto& test = type::get<Derived>();
	auto& test0 = type::get<Derived>();
	auto& test2 = type::get<Derived>().get_base_classes();
	auto& test3 = type::get<Derived>().get_derived_classes();
	auto& test4 = type::get<Derived>().get_properties();
	auto& other0 = type::get<Base>();
	auto& other1 = type::get<Intern>();

	for (auto& it : type::get<Derived>().get_base_classes())
		printf("%s\n", it.get_name());

	Base* tmp0 = new Base();
	Base* tmp1 = new Derived();
	int* tmp2 = new int();
	Intern* tmp3 = new Intern();
	Intern tmp4 = Intern();

	auto& test5 = type::get(tmp0);
	auto& test6 = type::get(tmp1);
	auto& test7 = type::get(&tmp4);
	//auto& test95 = type::get(tmp4);
	//auto& test231 = type::get(5);

	auto test8 = type::cast<Base*>(&tmp4);
	auto test9 = type::cast<Derived*>(tmp0);

	auto test10 = type::get<Derived>().get_factory().construct();
	type::get<Derived>().get_factory().destroy(test10);
	auto test11 = reflectpp::type_info::get<Intern>();

	variant var1 = variant(tmp0);
	variant var2 = var1;
	variant var3 = variant(tmp3);
	//variant var4 = variant(&tmp4);

	auto& tmp55 = var1.get_type();
	auto tmp56 = var1.is_type<Base>();
	auto& tmp57 = var1.get_value<Base>();

	auto other5 = type::get<Base>().create();

	tmp0->SetValue(5.f);
	tmp0->SetValue1(6.0);
	//tmp0->value.zvalue0 = -1;
	//tmp0->value.zvalue1 = 15;
	tmp3->InternValue0 = 12.f;
	tmp3->InternValue1 = 13.0;

	auto varssss = type::get<Intern>().create();
	Intern intern;
	intern.InternValue0 = 5363.f;
	intern.InternValue1 = 53634.0;

	for (auto& prop : type::get<Intern>().get_properties())
	{
		//Variant var = prop.GetValue(tmp3);
		variant var = prop.get_value(var3);

		if (var.is_type<double>())
			printf("%s is a double : %f\n", prop.get_name(), var.get_value<double>());
		else if (var.is_type<float>())
			printf("%s is a float : %f\n", prop.get_name(), var.get_value<float>());
	}

	for (auto& prop : type::get<Base>().get_properties())
	{
		//Variant var = prop.GetValue(tmp3);
		variant var = prop.get_value(tmp0);

		if (var.is_type<double>())
			printf("%s is a double : %f\n", prop.get_name(), var.get_value<double>());
		else if (var.is_type<float>())
			printf("%s is a float : %f\n", prop.get_name(), var.get_value<float>());
	}
	/*
	// Serialization test
	serializer seri("test");
	//seri.save(tmp0);
	Base* tmpload = new Base();
	variant var22 = variant(tmpload);
	for (auto& prop : var22.get_type().get_properties())
	{
		variant pvar{ prop.get_value(var22) };

		if (pvar.is_type<float>())
		{
			pvar.get_value<float>() = 12.f;

			auto temp = pvar.get_value<float>();
			auto& temp2 = pvar.get_value<float>();

			temp = 15.f;
			temp2 = 16.f;

			Base& base = var22.get_value<Base>();
			Base& base563 = var22.get_value<Base>();
		}
		else if (pvar.is_type<double>())
		{
			pvar.get_value<double>() = 13.0;
		}
	}

	seri.load(tmpload);

	delete tmpload;*/

	delete tmp0;
	delete tmp1;
	delete tmp2;
	delete tmp3;

	// Exit point
	printf("\nExit Success!\n\n");

	return EXIT_SUCCESS;
}
