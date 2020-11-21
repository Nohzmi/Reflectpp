// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>
#include <iostream>////

#include "property.h"
#include "type.h"

using json = nlohmann::json;

namespace reflectpp
{
	serializer::serializer(const char* path)
	{
		m_path = std::string(path) + ".json";
	}

	void serializer::save(const variant& var) const noexcept
	{
		json j;
		save_type(var, j);

		std::ofstream out(m_path);
		out << std::setw(4) << j;
	}

	void serializer::save_type(const variant& var, json& j) const noexcept
	{
		for (property& prop : var.get_type().get_properties())
		{
			variant pvar{ prop.get_value(var) };

			if (prop.get_type() == type::get<int>())
				j.emplace(prop.get_name(), pvar.get_value<int>());
			if (prop.get_type() == type::get<unsigned>())
				j.emplace(prop.get_name(), pvar.get_value<unsigned>());
			else if (prop.get_type() == type::get<float>())
				j.emplace(prop.get_name(), pvar.get_value<float>());
			else if (prop.get_type() == type::get<double>())
				j.emplace(prop.get_name(), pvar.get_value<double>());
			else
			{
				auto& pj = j[prop.get_name()];
				save_type(pvar, pj);
			}
		}
	}

	void serializer::load(variant& var) const noexcept
	{
		json j;

		std::ifstream in(m_path);

		if (!in.is_open())
			return;

		in >> j;

		load_type(var, j);
		
		std::cout << j.dump(4) << std::endl;///////
	}

	void serializer::load_type(variant& var, const nlohmann::json& j) const noexcept
	{
		for (property& prop : var.get_type().get_properties())
		{
			if (!j.contains(prop.get_name()))
				continue;

			variant pvar{ prop.get_value(var) };
			auto& pj{ j.at(prop.get_name()) };

			if (pj.is_number_integer())
			{
				if (pvar.is_type<int>())
					pvar.get_value<int>() = pj.get<int>();
				else if (pvar.is_type<unsigned>())
					pvar.get_value<unsigned>() = pj.get<unsigned>();
			}
			else if (pj.is_number_float())
			{
				if (pvar.is_type<float>())
					pvar.get_value<float>() = pj.get<float>();
				else if(pvar.is_type<double>())
					pvar.get_value<double>() = pj.get<double>();
			}
			else
				load_type(pvar, pj);
		}
	}
}
