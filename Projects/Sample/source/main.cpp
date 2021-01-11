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

using namespace reflectpp;

int main()
{
	Window app;
	app.Update();

	// Entry point
	std::cout << "Entry point" << std::endl;
	serializer serialize("test");

	// Serialization test (save)
	Base* temp = new Base();
	//temp->BaseValue0 = 10.f;
	//temp->BaseValue1 = 11.0;
	//temp->BaseValue3 = 12.0;
	//temp->BaseValue4 = 13.0;
	//temp->value.zvalue0 = 20;
	//temp->value.zvalue1 = 21;
	//serialize.save(*temp);

	// Serialization test (save)
	serialize.load(*temp);

	// Exit point
	delete temp;
	printf("\nExit Success!\n\n");

	return EXIT_SUCCESS;
}
