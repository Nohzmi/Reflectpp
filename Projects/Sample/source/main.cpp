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

#include "window.h"


class Test
{
public:
	Test() = default;
	~Test() = default;
	Test(const Test&) = default;
	Test(Test&&) REFLECTPP_NOEXCEPT = default;
	Test& operator=(const Test&) = default;
	Test& operator=(Test&&) REFLECTPP_NOEXCEPT = default;
public:

	int sdjhflsdq;
	int sdjhflsdq2;
};

using namespace reflectpp;

int main()
{
	printf("Entry point\n");

	//Window app;
	//app.Update();

	printf("\nExit Success!\n\n");

	// Test area
	Derived d = Derived();
	d.DerivedValue1 = 1.f;
	d.DerivedValue0.push_back(10.f);
	d.DerivedValue0.push_back(11.f);
	d.DerivedValue0.push_back(12.f);

	serializer s("test");
	s.save(d);

	/*d.DerivedValue0.push_back(10.f);
	d.DerivedValue0.push_back(11.f);
	d.DerivedValue0.push_back(12.f);

	variant var = type::get<Derived>().get_property("DerivedValue0").get_value(d);
	variant_sequencial_view variant_sequence = var.create_sequential_view();

	for (auto it = variant_sequence.begin(); it != variant_sequence.end(); ++it)
	{
		auto test = it.get_data();
		float getted = test.get_value<float>();
		std::cout << getted << std::endl;
	}

	variant_sequence.set_value(0, 0.f);
	variant_sequence.set_value(1, 1.f);
	variant_sequence.set_value(, 2.f);

	std::cout << variant_sequence.insert(variant_sequence.begin() + 1, 15.f).get_data().get_value<float>() << std::endl;
	std::cout << variant_sequence.get_size() << std::endl;*/

	//variant_sequence.set_size(12);

	//auto test = variant_sequence.get_value(0);
	//float getted = test.get_value<float>();
	//variant_sequence.clear();

	Test test{ 5, 6 };

	return EXIT_SUCCESS;
}
