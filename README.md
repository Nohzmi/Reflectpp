Reflectpp
====
> C++ Reflection Library

Reflectpp implement a reflection/serialization system in C++

How to Use
----------
## Manual registration
Derived.h
```cpp
#pragma once
#include <reflectpp/register.h>
#include "base.h"

class Derived : public Base
{
	REFLECT(Derived)

public:

	int data;
};
```
Derived.cpp
```cpp
#include <reflectpp/registration.h>
#include "example.h"

REGISTRATION
{
	reflectpp::registration::class_<Derived>().base<Base>()
	.property("data", &Derived::data);
}
```

Features
---------
- Reflection:
	- Register classes, properties or enums
	- Support custom sequence container (std::vector, ...)
	- Support custom associative container (std::map, ...)
	- Support custom wrapper (std::unique_ptr, ...)
	- Implement custom casting
	- Independant factory and type_info class helper
	- Variant for any reflected types with specialized view for containers
	- Minimal macro usage
- Serialization:
	- Save and load for reflected classes

Portability
-----------
Tested and compiled with:
- Microsoft Visual Studio 2019 (x86 or x64)
- Support c++17 or more