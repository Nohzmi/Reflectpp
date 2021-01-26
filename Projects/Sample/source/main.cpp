// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <iostream>
#include <unordered_map>
#include <map>
#include <type.h>
#include <factory.h>
#include <type_info.h>
#include <variant.h>
#include <property.h>
#include <serializer.h>
#include <instance.h>
#include <variant_associative_view.h>
#include <variant_sequencial_view.h>
#include <argument.h>
#include <vld/vld.h>

#include "intern.h"
#include "base.h"
#include "derived.h"

#include "window.h"

using namespace reflectpp;

int main()
{
	//******************//
	//***** Sample *****//

	//Window app;
	//app.Update();

	//***********************************//
	//***** variant sequencial view *****//

	std::cout << std::endl;
	std::cout << "//***********************************//" << std::endl;
	std::cout << "//***** variant sequencial view *****//" << std::endl;
	std::cout << std::endl;

	Derived object = Derived();
	variant var = type::get<Derived>().get_property("DerivedValue2").get_value(object);

	float get_as_float = var.get_value<float>();
	double gat_as_double = var.get_value<double>();

	variant_sequencial_view variant_sequence = var.create_sequential_view();
	variant_sequence.set_size(2);
	variant_sequence.set_value(0, 0.f);
	variant_sequence.set_value(1, 1.f);
	variant_sequence.insert(variant_sequence.begin() + 2, 2.f);
	variant_sequence.erase(variant_sequence.begin() + 1);

	std::cout << "size: " << variant_sequence.get_size() << std::endl << "values: ";
	for (auto it : variant_sequence)
		std::cout << it.get_value<float>() << " ";
	std::cout << std::endl << std::endl;

	std::cout << "type: " << variant_sequence.get_type().get_name() << std::endl;
	std::cout << "is_dynamic: " << variant_sequence.is_dynamic() << std::endl;
	std::cout << "is_empty: " << variant_sequence.is_empty() << std::endl;
	std::cout << "is_valid: " << variant_sequence.is_valid() << std::endl << std::endl;

	variant_sequence.clear();
	std::cout << "clear" << std::endl;
	std::cout << "size: " << variant_sequence.get_size() << std::endl;
	std::cout << std::endl;

	//************************************//
	//***** variant associative view *****//

	std::cout << "//************************************//" << std::endl;
	std::cout << "//***** variant associative view *****//" << std::endl;
	std::cout << std::endl;

	var = type::get<Derived>().get_property("DerivedValue3").get_value(object);
	variant_associative_view variant_associative = var.create_associative_view();
	variant_associative.insert('a', 1.f);
	variant_associative.insert('b', 2.f);
	variant_associative.insert('c', 3.f);

	auto insert = variant_associative.insert('a', 5.f);
	std::cout << "insertion: " << insert.second << ", { " << insert.first.get_key().get_value<char>()
		<< ", " << insert.first.get_value().get_value<float>() << " }" << std::endl << std::endl;

	auto equal_range = variant_associative.equal_range('b');
	const char* range_start = equal_range.first == variant_associative.begin() ? "begin" : (equal_range.first == variant_associative.end() ? "end" : "it");
	const char* range_end = equal_range.second == variant_associative.begin() ? "begin" : (equal_range.second == variant_associative.end() ? "end" : "it");
	std::cout << "equal_range: " << range_start << " " << range_end << std::endl << std::endl;

	auto findz = variant_associative.find('z');
	auto findc = variant_associative.find('c');
	std::cout << "find: " << (findz != variant_associative.end()) << std::endl;
	std::cout << "find: " << (findc != variant_associative.end()) << std::endl << std::endl;

	std::cout << "erase: " << variant_associative.erase('z') << std::endl;
	std::cout << "erase: " << variant_associative.erase('b') << std::endl << std::endl;

	std::cout << "size: " << variant_associative.get_size() << std::endl;
	for (auto it : variant_associative)
		std::cout << "{ " << it.first.get_value<char>() << ", " << it.second.get_value<float>() << " } ";
	std::cout << std::endl << std::endl;

	std::cout << "is_empty: " << variant_associative.is_empty() << std::endl;
	std::cout << "is_valid: " << variant_associative.is_valid() << std::endl;
	std::cout << std::endl;

	variant_associative.clear();
	std::cout << "size: " << variant_associative.get_size() << std::endl;
	for (auto it : variant_associative)
		std::cout << "{ " << it.first.get_value<char>() << ", " << it.second.get_value<float>() << " } ";
	std::cout << std::endl << std::endl;

	//serializer s("test");
	//s.save(object);

	return EXIT_SUCCESS;
}
