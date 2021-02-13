// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>

#include "argument.h"
#include "instance.h"
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

	void serializer::save(instance object) const REFLECTPP_NOEXCEPT  //////
	{
		json j;
		variant* var{ static_cast<variant*>(object) };
		save_type(*var, j);

		std::ofstream out(m_path);
		out << std::setw(4) << j;
	}

	void serializer::load(instance object) const REFLECTPP_NOEXCEPT   /////
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
		if (!var.is_valid())
		{
			return;
		}
		else if (var.is_type<bool>())
		{
			if (!j.is_array()) j = var.get_value<bool>();
			else j.emplace_back(var.get_value<bool>());
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
		else if (var.is_type<long double>())
		{
			if (!j.is_array()) j = var.get_value<long double>();
			else j.emplace_back(var.get_value<long double>());
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
		else if (var.is_type<long>())
		{
			if (!j.is_array()) j = var.get_value<long>();
			else j.emplace_back(var.get_value<long>());
		}
		else if (var.is_type<int64_t>())
		{
			if (!j.is_array()) j = var.get_value<int64_t>();
			else j.emplace_back(var.get_value<int64_t>());
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
		else if (var.is_type<unsigned long>())
		{
			if (!j.is_array()) j = var.get_value<unsigned long>();
			else j.emplace_back(var.get_value<unsigned long>());
		}
		else if (var.is_type<uint64_t>())
		{
			if (!j.is_array()) j = var.get_value<uint64_t>();
			else j.emplace_back(var.get_value<uint64_t>());
		}
		else if (var.is_type<char>())
		{
			if (!j.is_array()) j = std::string(1, var.get_value<char>());
			else j.emplace_back(std::string(1, var.get_value<char>()));
		}
		else if (var.is_type<char16_t>())
		{
			if (!j.is_array()) j = var.get_value<char16_t>();
			else j.emplace_back(var.get_value<char16_t>());
		}
		else if (var.is_type<char32_t>())
		{
			if (!j.is_array()) j = var.get_value<char32_t>();
			else j.emplace_back(var.get_value<char32_t>());
		}
		else if (var.is_type<wchar_t>())
		{
			if (!j.is_array()) j = var.get_value<wchar_t>();
			else j.emplace_back(var.get_value<wchar_t>());
		}
		else if (var.is_associative_container())
		{
			j = json::array();
			auto view{ var.create_associative_view() };

			for (auto it : view)
			{
				json obj = json::object();
				save_type(it.first, obj["key"]);

				if (!view.is_key_only_type())
					save_type(it.second, obj["value"]);

				j.emplace_back(obj);
			}
		}
		else if (var.is_sequential_container())
		{
			auto view{ var.create_sequential_view() };
			
			if (view.get_value_type() == type::get<char>())
			{
				std::string str;

				for (auto it : view)
					str.push_back(it.get_value<char>());

				if (!j.is_array()) j = str;
				else j.emplace_back(str);
			}
			else
			{
				if (!j.is_array())
				{
					j = json::array();

					for (auto it : view)
						save_type(it, j);
				}
				else
				{
					j.emplace_back(json::array());

					for (auto it : view)
						save_type(it, *(j.end()-1));
				}
			}
		}
		else if (var.get_type().is_class())
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
		if (j.is_null() || !var.is_valid())
		{
			return;
		}
		else if (j.is_boolean())
		{
			if (var.is_type<bool>())
				var.get_value<bool>() = j.get<bool>();
		}
		else if (j.is_number_float())
		{
			if (var.is_type<float>()) var.get_value<float>() = j.get<float>();
			else if (var.is_type<double>()) var.get_value<double>() = j.get<double>();
			else if (var.is_type<long double>()) var.get_value<long double>() = j.get<long double>();
		}
		else if (j.is_number_integer())
		{
			if (var.is_type<int8_t>()) var.get_value<int8_t>() = j.get<int8_t>();
			else if (var.is_type<int16_t>()) var.get_value<int16_t>() = j.get<int16_t>();
			else if (var.is_type<int32_t>()) var.get_value<int32_t>() = j.get<int32_t>();
			else if (var.is_type<long>()) var.get_value<long>() = j.get<long>();
			else if (var.is_type<int64_t>()) var.get_value<int64_t>() = j.get<int64_t>();
			else if (var.is_type<uint8_t>()) var.get_value<uint8_t>() = j.get<uint8_t>();
			else if (var.is_type<uint16_t>()) var.get_value<uint16_t>() = j.get<uint16_t>();
			else if (var.is_type<uint32_t>()) var.get_value<uint32_t>() = j.get<uint32_t>();
			else if (var.is_type<unsigned long>()) var.get_value<unsigned long>() = j.get<unsigned long>();
			else if (var.is_type<uint64_t>()) var.get_value<uint64_t>() = j.get<uint64_t>();
			else if (var.is_type<char16_t>()) var.get_value<char16_t>() = j.get<char16_t>();
			else if (var.is_type<char32_t>()) var.get_value<char32_t>() = j.get<char32_t>();
			else if (var.is_type<wchar_t>()) var.get_value<wchar_t>() = j.get<wchar_t>();
		}
		else if (j.is_string())
		{
			if (var.is_type<char>())
			{
				std::string str{ j.get<std::string>() };
				var.get_value<char>() = str.at(0);
			}
			else if (var.is_sequential_container())
			{
				auto view{ var.create_sequential_view() };
				view.clear();

				for (auto& it : j.get<std::string>())
					view.insert(view.end(), it);
			}
		}
		else if (j.is_array())
		{
			if (var.is_associative_container())
			{
				auto view{ var.create_associative_view() };
				view.clear();

				for (auto& it : j)
				{
					if (!it.is_object() || !it.contains("key"))
						continue;

					variant key_var{ view.get_key_type().create() };
					variant value_var{ view.get_value_type().create() };
					load_type(key_var, it.at("key"));

					if (it.contains("value"))
						load_type(value_var, it.at("value"));

					view.insert(key_var, value_var);
				}
			}
			else if (var.is_sequential_container())
			{
				auto view{ var.create_sequential_view() };
				view.clear();

				for (auto& it : j)
				{
					variant value_var{ view.get_value_type().create() };
					load_type(value_var, it);

					view.insert(view.end(), value_var);
				}
			}
		}
		else if (j.is_object())
		{
			for (auto& it : var.get_type().get_properties())
			{
				if (!j.contains(it.get_name()))
					continue;

				variant pvar{ it.get_type().create() };
				load_type(pvar, j.at(it.get_name()));

				it.set_value(var, pvar);
			}
		}
	}
}
