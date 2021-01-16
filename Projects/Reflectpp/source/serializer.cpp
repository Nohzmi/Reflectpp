// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>

#include "property.h"
#include "type.h"
#include "variant_sequencial_view.h"

using json = nlohmann::json;

namespace reflectpp
{
	serializer::serializer(const char* path)
	{
		m_path = std::string(path) + ".json";
	}

	void serializer::save(instance object) const REFLECTPP_NOEXCEPT
	{
		json j;
		save_type(*object.m_variant, j);

		std::ofstream out(m_path);
		out << std::setw(4) << j;
	}

	void serializer::load(instance object) const REFLECTPP_NOEXCEPT
	{
		json j;

		std::ifstream in(m_path);

		if (!in.is_open())
			return;

		in >> j;

		load_type(*object.m_variant, j);
	}

	void serializer::save_type(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_type<int>())
		{
			if (!j.is_array()) j = var.get_value<int>();
			else j.emplace_back(var.get_value<int>());
		}
		else if (var.is_type<unsigned>())
		{
			if (!j.is_array()) j = var.get_value<unsigned>();
			else j.emplace_back(var.get_value<unsigned>());
		}
		else if (var.is_type<float>())
		{
			if (!j.is_array()) j = var.get_value<float>();
			else j.emplace_back(var.get_value<float>());
		}
		else if (var.is_type<double>())
		{
			if (!j.is_array()) j = var.get_value<double>();
			else j.emplace_back(var.get_value<double>());
		}
		else if (var.is_sequential_container())
		{
			j = json::array();

			for (auto v : var.create_sequential_view())
				save_type(v, j);
		}
		else
		{
			for (auto it : var.get_type().get_properties())
			{
				if ((it.get_specifiers() & specifiers::Serialized) == 0)
					continue;

				save_type(it.get_value(var), j[it.get_name()]);
			}
		}
	}

	void serializer::load_type(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		/*for (property& prop : var.get_type().get_properties())
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
		}*/

		/////////////////////////////////////

		/*if (j.is_number_integer())
		{
			if (var.is_type<int>())
				prop.set_value(var, j.get<int>());
			else if (var.is_type<unsigned>())
				prop.set_value(var, j.get<unsigned>());
		}
		else if (j.is_number_float())
		{
			if (var.is_type<float>())
				prop.set_value(var, j.get<float>());
			else if (var.is_type<double>())
				prop.set_value(var, j.get<double>());
		}
		else if (j.is_array())
		else
		{
			load_type(pvar, pj);
		}

		for (property& prop : var.get_type().get_properties())
		{
			if (!j.contains(prop.get_name()))
				continue;

			if ((prop.get_specifiers() & specifiers::Serialized) == 0)
				continue;

			variant pvar{ prop.get_value(var) };
			auto& pj{ j.at(prop.get_name()) };

			
		}*/
	}
}
