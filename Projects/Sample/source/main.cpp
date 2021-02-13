// Copyright (c) 2020, Nohzmi. All rights reserved.

#include <iostream>
#include <unordered_map>
#include <map>
#include <reflectpp.h>
//#include <vld/vld.h>

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
	//variant var = type::get<Derived>().get_property("DerivedValue2").get_value(object);
	variant var = variant(object.DerivedValue2);

	instance intance00 = object;
	instance intance02 = intance00;

	variant_sequential_view variant_sequence = var.create_sequential_view();
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

	/*variant_sequence.clear();
	std::cout << "clear" << std::endl;
	std::cout << "size: " << variant_sequence.get_size() << std::endl;
	std::cout << std::endl;*/

	//************************************//
	//***** variant associative view *****//

	std::cout << "//************************************//" << std::endl;
	std::cout << "//***** variant associative view *****//" << std::endl;
	std::cout << std::endl;

	var = type::get<Derived>().get_property("DerivedValue3").get_value(object);
	variant_associative_view variant_associative = var.create_associative_view();
	variant_associative.insert('a', 1.f);
	variant_associative.insert('b', 2.0);
	variant_associative.insert('c', 3.0);
	//variant_associative.insert('a');
	//variant_associative.insert('b');
	//variant_associative.insert('c');

	auto insert = variant_associative.insert('a', 5.f);
	char key = insert.first.get_key().is_valid() ? insert.first.get_key().get_value<char>() : '0';
	float value = insert.first.get_value().is_valid() ? insert.first.get_value().get_value<float>() : -1;
	std::cout << "insertion: " << insert.second << ", { " << key << ", " << value << " }" << std::endl << std::endl;

	auto equal_range = variant_associative.equal_range('b');
	const char* range_start = equal_range.first == variant_associative.begin() ? "begin" : (equal_range.first == variant_associative.end() ? "end" : "it");
	const char* range_end = equal_range.second == variant_associative.begin() ? "begin" : (equal_range.second == variant_associative.end() ? "end" : "it");
	std::cout << "equal_range: " << range_start << " " << range_end << std::endl << std::endl;

	auto findz = variant_associative.find('z');
	auto findc = variant_associative.find('c');
	std::cout << "find: " << (findz != variant_associative.end()) << std::endl;
	std::cout << "find: " << (findc != variant_associative.end()) << std::endl << std::endl;

	std::cout << "erase: " << variant_associative.erase('z') << std::endl;
	std::cout << "erase: " << variant_associative.erase('c') << std::endl << std::endl;

	std::cout << "size: " << variant_associative.get_size() << std::endl;
	for (auto it : variant_associative)
	{
		char key0 = it.first.is_valid() ? it.first.get_value<char>() : '0';
		float value0 = it.second.is_valid() ? it.second.get_value<float>() : -1;
		std::cout << "{ " << key0 << ", " << value0 << " } ";
	}
	std::cout << std::endl << std::endl;

	std::cout << "is_empty: " << variant_associative.is_empty() << std::endl;
	std::cout << "is_valid: " << variant_associative.is_valid() << std::endl;
	std::cout << "is_key_only_type: " << variant_associative.is_key_only_type() << std::endl;
	std::cout << std::endl;
	
	/*variant_associative.clear();
	std::cout << "size: " << variant_associative.get_size() << std::endl;
	for (auto it : variant_associative)
		std::cout << "{ " << it.first.get_value<char>() << ", " << it.second.get_value<float>() << " } ";
	std::cout << std::endl << std::endl;*/

	//*********************//
	//***** enum test *****//

	std::cout << "//*********************//" << std::endl;
	std::cout << "//***** enum test *****//" << std::endl;
	std::cout << std::endl;

	auto AlignmentType = reflectpp::type::get<E_Alignment>();

	if (AlignmentType.is_enumeration())
	{
		auto AlignmentEnum = AlignmentType.get_enumeration();
		std::cout << "name: " << AlignmentEnum.get_name() << std::endl;
		std::cout << "type: " << AlignmentEnum.get_type().get_name() << std::endl;
		std::cout << "underlying type: " << AlignmentEnum.get_underlying_type().get_name() << std::endl;
		std::cout << std::endl;

		auto AlignmentNames = AlignmentEnum.get_names();
		auto AlignmentValues = AlignmentEnum.get_values();

		std::cout << "enum class E_Alignment" << std::endl;
		for (int i = 0; i < AlignmentNames.size(); ++i)
		{
			std::cout << "name: " << AlignmentNames[i] << ", value: " << AlignmentValues[i].get_value<size_t>() << std::endl;
		}
		std::cout << std::endl;

		std::cout << "name to value: \"AlignLeftvalue\" -> " << AlignmentEnum.name_to_value("AlignLeft").get_value<size_t>() << std::endl;
		std::cout << "value to name: 0 -> " << AlignmentEnum.value_to_name(E_Alignment::AlignLeft) << std::endl;
		std::cout << "value to name: 2 -> " << AlignmentEnum.value_to_name(2) << std::endl;
	}
	std::cout << std::endl;

	//**********************//
	//***** other test *****//

	std::cout << "//**********************//" << std::endl;
	std::cout << "//***** other test *****//" << std::endl;
	std::cout << std::endl;

	Base* ksjqdbfskjf = new Derived();
	auto float_var = variant(*ksjqdbfskjf);
	std::cout << "type: " << float_var.get_type().get_name() << ", value:" << std::endl;
	std::cout << "can convert to double: " << float_var.can_convert<Base*>() << std::endl;
	float_var.convert<Base*>();
	std::cout << "type: " << float_var.get_type().get_name() << ", value:" << std::endl;
	std::cout << std::endl;

	std::cout << "get_type_by_name: Base, getted: " << type::get_by_name("Base").get_name() << std::endl;
	std::cout << std::endl;

	std::cout << "get all types" << std::endl;
	for (auto& it : type::get_types())
		std::cout << "  " << it.get_name() << std::endl;
	std::cout << std::endl;

	//******************************//
	//***** serialization test *****//

	std::cout << "//******************************//" << std::endl;
	std::cout << "//***** serialization test *****//" << std::endl;
	std::cout << std::endl;

	Intern intern;
	intern.InternValue0 = -11;
	intern.InternValue1 = 100;

	object.SetValue0(-20.f);
	object.SetValue1(intern);
	object.DerivedValue0 = 10.f;
	object.DerivedValue1.InternValue0 = 20;
	object.DerivedValue1.InternValue1 = 21;
	object.DerivedValue4.emplace('x');
	object.DerivedValue4.emplace('y');
	object.DerivedValue4.emplace('z');

	serializer s("test");
	s.save(object);

	Derived object2 = Derived();
	s.load(object2);

	return EXIT_SUCCESS;
}
