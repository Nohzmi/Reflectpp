// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file typedef.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>

namespace reflectpp
{
	namespace details
	{
		using AssociativeClear = void (*)(void*);
		using AssociativeErase = void (*)(void*, void*);
		using AssociativeFind = void* (*)(void*, void*);
		using AssociativeInsert = void (*)(void*, void*, void*);
		using AssociativeSize = size_t(*)(void*);
		using Constructor = void* (*)();
		using Copy = void* (*)(void*);
		using Destructor = void (*)(void*);
		using Getter = std::function<void* (void*, bool&)>;
		using SequenceAssign = void (*)(void*, size_t, void*);
		using SequenceAt = void* (*)(void*, size_t);
		using SequenceClear = void (*)(void*);
		using SequenceErase = void (*)(void*, size_t);
		using SequenceInsert = void (*)(void*, size_t, void*);
		using SequenceResize = void (*)(void*, size_t);
		using SequenceSize = size_t (*)(void*);
		using Setter = std::function<void(void*, void*)>;
	}
}