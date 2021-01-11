// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>

#include "property.h"
#include "type.h"

using json = nlohmann::json;

namespace reflectpp
{
	serializer::serializer(const char* path)
	{
		m_path = std::string(path) + ".json";
	}

	void serializer::save(const instance& object) const REFLECTPP_NOEXCEPT
	{
		json j;
		save_type(*object.m_var, j);

		std::ofstream out(m_path);
		out << std::setw(4) << j;
	}

	void serializer::load(const instance& object) const REFLECTPP_NOEXCEPT
	{
		json j;

		std::ifstream in(m_path);

		if (!in.is_open())
			return;

		in >> j;

		load_type(*object.m_var, j);
	}

	void serializer::save_type(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		for (property& prop : var.get_type().get_properties())
		{
			if ((prop.get_specifiers() & specifiers::Serialized) == 0)
				continue;

			variant pvar{ prop.get_value(var) };

			if (pvar.is_type<int>())
				j.emplace(prop.get_name(), pvar.get_value<int>());
			else if (pvar.is_type<unsigned>())
				j.emplace(prop.get_name(), pvar.get_value<unsigned>());
			else if (pvar.is_type<float>())
				j.emplace(prop.get_name(), pvar.get_value<float>());
			else if (pvar.is_type<double>())
				j.emplace(prop.get_name(), pvar.get_value<double>());
			else
			{
				auto& pj = j[prop.get_name()];
				save_type(pvar, pj);
			}
		}
	}

	void serializer::load_type(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		for (property& prop : var.get_type().get_properties())
		{
			if (!j.contains(prop.get_name()))
				continue;

			if ((prop.get_specifiers() & specifiers::Serialized) == 0)
				continue;

			variant pvar{ prop.get_value(var) };
			auto& pj{ j.at(prop.get_name()) };

			if (pj.is_number_integer())
			{
				if (pvar.is_type<int>())
					prop.set_value(var, pj.get<int>());
				else if (pvar.is_type<unsigned>())
					prop.set_value(var, pj.get<unsigned>());
			}
			else if (pj.is_number_float())
			{
				if (pvar.is_type<float>())
					prop.set_value(var, pj.get<float>());
				else if(pvar.is_type<double>())
					prop.set_value(var, pj.get<double>());
			}
			else
			{
				load_type(pvar, pj);
			}
		}
	}
}
