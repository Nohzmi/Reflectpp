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
	printf("Entry point\n");

	Window app;
	app.Update();

	printf("\nExit Success!\n\n");




	/*serializer serialize("test");

	// Serialization test (save)
	Base* temp = new Base();

	// Serialization test (save)
	serialize.load(*temp);

	// Exit point
	delete temp;*/
	

	return EXIT_SUCCESS;
}
