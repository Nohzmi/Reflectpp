// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>

#include "argument.h"
#include "property.h"
#include "type.h"
#include "variant_associative_view.h"
#include "variant_sequential_view.h"

using json = nlohmann::json;

namespace reflectpp
{
	serializer::serializer(const char*) REFLECTPP_NOEXCEPT
	{
		m_path = "temp.json";// (std::string(path) + ".json").c_str();//TODO clean
	}

	void serializer::save(instance object) const REFLECTPP_NOEXCEPT
	{
		json j;
		variant* var{ static_cast<variant*>(object) };
		save_type(*var, j);

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

		load_type(*static_cast<variant*>(object), j);
	}

	void serializer::save_type(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_type<bool>())
		{
			if (!j.is_array()) j = var.get_value<bool>();
			else j.emplace_back(var.get_value<bool>());
		}
		else if (var.is_type<char>())
		{
			if (!j.is_array()) j = std::string(1, var.get_value<char>()); // � check
			else j.emplace_back(std::string(1, var.get_value<char>()));
		}
		else if (var.is_type<double>())
		{
			if (!j.is_array()) j = var.get_value<double>();
			else j.emplace_back(var.get_value<double>());
		}
		else if (var.is_type<float>())
		{
			if (!j.is_array()) j = var.get_value<float>();
			else j.emplace_back(var.get_value<float>());
		}
		else if (var.is_type<int8_t>())
		{
			if (!j.is_array()) j = var.get_value<int8_t>();
			else j.emplace_back(var.get_value<int8_t>());
		}
		else if (var.is_type<int16_t>())
		{
			if (!j.is_array()) j = var.get_value<int16_t>();
			else j.emplace_back(var.get_value<int16_t>());
		}
		else if (var.is_type<int32_t>())
		{
			if (!j.is_array()) j = var.get_value<int32_t>();
			else j.emplace_back(var.get_value<int32_t>());
		}
		else if (var.is_type<int64_t>())
		{
			if (!j.is_array()) j = var.get_value<int64_t>();
			else j.emplace_back(var.get_value<int64_t>());
		}
		else if (var.is_type<long>())
		{
			if (!j.is_array()) j = var.get_value<long>();
			else j.emplace_back(var.get_value<long>());
		}
		else if (var.is_type<long double>())
		{
			if (!j.is_array()) j = var.get_value<long double>();
			else j.emplace_back(var.get_value<long double>());
		}
		else if (var.is_type<uint8_t>())
		{
			if (!j.is_array()) j = var.get_value<uint8_t>();
			else j.emplace_back(var.get_value<uint8_t>());
		}
		else if (var.is_type<uint16_t>())
		{
			if (!j.is_array()) j = var.get_value<uint16_t>();
			else j.emplace_back(var.get_value<uint16_t>());
		}
		else if (var.is_type<uint32_t>())
		{
			if (!j.is_array()) j = var.get_value<uint32_t>();
			else j.emplace_back(var.get_value<uint32_t>());
		}
		else if (var.is_type<uint64_t>())
		{
			if (!j.is_array()) j = var.get_value<uint64_t>();
			else j.emplace_back(var.get_value<uint64_t>());
		}
		else if (var.is_type<unsigned long>())
		{
			if (!j.is_array()) j = var.get_value<unsigned long>();
			else j.emplace_back(var.get_value<unsigned long>());
		}
		else if (var.is_associative_container())
		{
			j = json::array();

			for (auto it : var.create_associative_view())
			{
				json obj = json::object();
				save_type(it.first, obj["key"]);
				save_type(it.second, obj["value"]);
				j.emplace_back(obj);
			}
		}
		else if (var.is_sequential_container())
		{
			j = json::array();

			for (auto it : var.create_sequential_view())
				save_type(it, j);
		}
		else
		{
			for (auto& it : var.get_type().get_properties())
			{
				if ((it.get_specifiers() & specifiers::Serialized) == 0)
					continue;

				save_type(it.get_value(var), j[it.get_name()]);
			}
		}
	}

	void serializer::load_type(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (j.is_string())
		{
			if (var.is_type<char>()) var.get_value<char>() = j.get<char>();
			else if (!var.is_valid())
			{
				auto str = j.get<std::string>();

				if (str.size() == 1)
					var = variant(std::move(j.get<std::string>()[0]));
			}
		}
		else if (j.is_number_integer())
		{
			if (var.is_type<int>())
				var.get_value<int>() = j.get<int>();
			else if (var.is_type<unsigned>())
				var.get_value<unsigned>() = j.get<unsigned>();
			else if (!var.is_valid())
				var = variant(j.get<int>());
		}
		else if (j.is_number_float())
		{
			if (var.is_type<float>())
				var.get_value<float>() = j.get<float>();
			else if (var.is_type<double>())
				var.get_value<double>() = j.get<double>();
			else if (!var.is_valid())
				var = variant(j.get<float>());
		}
		else if (j.is_array())
		{
			if (var.is_associative_container())
			{
				auto v{ var.create_associative_view() };
				v.clear();
				
				for (auto& it : j)
				{
					variant l1;
					variant l2;
					load_type(l1, it["key"]);
					load_type(l2, it["value"]);
					v.insert(l1, l2);
				}
			}
			else if (var.is_sequential_container())
			{
				auto v{ var.create_sequential_view() };
				v.clear();

				for (auto& it : j)
				{
					variant l1 = variant();
					load_type(l1, it);
					v.insert(v.end(), l1);
				}
			}
		}
		else
		{
			for (auto& it : var.get_type().get_properties())
			{
				if (!j.contains(it.get_name()))
					continue;

				variant pvar{ it.get_value(var) };
				auto& pj{ j.at(it.get_name()) };
				load_type(pvar, pj);
			}
		}
	}
}
