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
	Base* base_ptr = new Base();
	Intern* intern_ptr = new Intern();

	intern_ptr->InternValue0 = 1.f;
	intern_ptr->InternValue1 = 2.f;

	variant base_variant = variant(*base_ptr);
	variant intern_variant = variant(*intern_ptr);

	float base_value = 6.f;
	float intern_value = 7.f;
	double double_value = 16.f;

	for (auto& prop : type::get<Intern>().get_properties())
	{
		variant var = prop.get_value(intern_variant);
		if (var.is_type<float>()) prop.set_value(intern_variant, intern_value);
		if (var.is_type<double>()) prop.set_value(intern_variant, 16.0);

		if (var.is_type<double>())
			printf("%s is a double : %f\n", prop.get_name(), var.get_value<double>());
		else if (var.is_type<float>())
			printf("%s is a float : %f\n", prop.get_name(), var.get_value<float>());
	}

	for (auto& prop : type::get<Base>().get_properties())
	{
		variant var = prop.get_value(*base_ptr);
		if (var.is_type<float>()) prop.set_value(base_variant, 9.f);

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

	delete base_ptr;
	delete intern_ptr;

	// Exit point
	printf("\nExit Success!\n\n");

	return EXIT_SUCCESS;
}
