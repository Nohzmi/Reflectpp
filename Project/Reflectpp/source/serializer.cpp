// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>////

using namespace nlohmann;

namespace reflectpp
{
	serializer::serializer(const char* path)
	{
		m_path = std::string(path) + ".json";
	}

	void serializer::save(const variant& var) noexcept
	{
		json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

		std::ofstream out(m_path);
		out << j;
	}

	void serializer::load(variant& var) const noexcept
	{
		json j;

		std::ifstream in(m_path);

		if (!in.is_open())
			return;

		in >> j;
		
		std::cout << j.dump(4) << std::endl;
	}
}
