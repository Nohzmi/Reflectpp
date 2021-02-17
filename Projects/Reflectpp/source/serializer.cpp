// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "serializer.h"

#include <fstream>
#include <iomanip>

#include "argument.h"
#include "enumeration.h"
#include "instance.h"
#include "property.h"
#include "type.h"
#include "variant_associative_view.h"
#include "variant_sequential_view.h"
#include "variant_wrapper_view.h"

using json = nlohmann::json;

namespace reflectpp
{
	serializer::serializer(const char* path) REFLECTPP_NOEXCEPT :
		m_path{ path }
	{
	}

	void serializer::load(instance object) const REFLECTPP_NOEXCEPT
	{
		std::string path{ m_path };

		if (path.substr(path.find_last_of(".") + 1) != "json")
			path.append(".json");

		json j;
		std::ifstream in(path);

		if (!in.is_open())
			return;

		in >> j;

		load_type(*static_cast<variant*>(object), j);
	}

	void serializer::save(instance object) const REFLECTPP_NOEXCEPT
	{
		json j;
		save_type(*static_cast<variant*>(object), j);

		std::string path{ m_path };

		if (path.substr(path.find_last_of(".") + 1) != "json")
			path.append(".json");

		std::ofstream out(path);
		out << std::setw(4) << j;
	}

	void serializer::load_array(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_associative_container())
			load_array_associative(var, j);
		else if (var.is_sequential_container())
			load_array_sequential(var, j);
	}

	void serializer::load_array_associative(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
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

	void serializer::load_array_sequential(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		auto view{ var.create_sequential_view() };
		view.set_size(j.size());

		for (auto [it, i] = std::tuple{ j.begin(), 0u }; it != j.end(); ++it, ++i)
		{
			variant value_var{ view.get_value(i) };
			load_type(value_var, *it);
			view.set_value(i, value_var);
		}
	}

	void serializer::load_boolean(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_type<bool>())
			var.get_value<bool>() = j.get<bool>();
	}

	void serializer::load_number(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_type<char16_t>())
			var.get_value<char16_t>() = j.get<char16_t>();
		else if (var.is_type<char32_t>())
			var.get_value<char32_t>() = j.get<char32_t>();
		else if (var.is_type<double>())
			var.get_value<double>() = j.get<double>();
		else if (var.is_type<float>())
			var.get_value<float>() = j.get<float>();
		else if (var.is_type<int8_t>())
			var.get_value<int8_t>() = j.get<int8_t>();
		else if (var.is_type<int16_t>())
			var.get_value<int16_t>() = j.get<int16_t>();
		else if (var.is_type<int32_t>())
			var.get_value<int32_t>() = j.get<int32_t>();
		else if (var.is_type<int64_t>())
			var.get_value<int64_t>() = j.get<int64_t>();
		else if (var.is_type<long>())
			var.get_value<long>() = j.get<long>();
		else if (var.is_type<long double>())
			var.get_value<long double>() = j.get<long double>();
		else if (var.is_type<uint8_t>())
			var.get_value<uint8_t>() = j.get<uint8_t>();
		else if (var.is_type<uint16_t>())
			var.get_value<uint16_t>() = j.get<uint16_t>();
		else if (var.is_type<uint32_t>())
			var.get_value<uint32_t>() = j.get<uint32_t>();
		else if (var.is_type<uint64_t>())
			var.get_value<uint64_t>() = j.get<uint64_t>();
		else if (var.is_type<unsigned long>())
			var.get_value<unsigned long>() = j.get<unsigned long>();
		else if (var.is_type<wchar_t>())
			var.get_value<wchar_t>() = j.get<wchar_t>();
	}

	void serializer::load_object(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.get_type().is_class())
			load_object_class(var, j);
		else if (var.is_wrapper())
			load_object_wrapper(var, j);
	}

	void serializer::load_object_class(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		for (auto& it : var.get_type().get_properties())
		{
			if (!j.contains(it.get_name()))
				continue;

			auto pvar{ it.get_value(var) };
			load_type(pvar, j.at(it.get_name()));

			it.set_value(var, pvar);
		}
	}

	void serializer::load_object_wrapper(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (!j.contains("type") || !j.contains("value"))
			return;

		auto view{ var.create_wrapper_view() }; // TODO surement à revoir
		auto loaded_type{ type::get_by_name(j.at("type").get<std::string>().c_str()) };

		if (view.is_empty() || view.get_wrapped_value().get_type() != loaded_type)
		{
			variant ptr_var{ loaded_type.create() };
			load_type(ptr_var, j.at("value"));
			view.reset(std::move(ptr_var));
		}
		else
		{
			variant ptr_var{ view.get_wrapped_value() };
			load_type(ptr_var, j.at("value"));
		}
	}

	void serializer::load_string(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		std::string str{ j.get<std::string>() };

		if (var.is_type<char>())
			var.get_value<char>() = str.at(0);
		else if (var.get_type().is_enumeration())
			var = var.get_type().get_enumeration().name_to_value(str.c_str()); // TODO conversion string ?
		else if (var.is_sequential_container())
			load_string_container(var, j, str);
	}

	void serializer::load_string_container(variant& var, const nlohmann::json& j, const std::string& str) const REFLECTPP_NOEXCEPT
	{
		auto view{ var.create_sequential_view() };
		view.set_size(str.size());

		for (auto [it, i] = std::tuple{ str.begin(), 0u }; it != str.end(); ++it, ++i)
			view.set_value(i, *it);
	}

	void serializer::load_type(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT
	{
		if (j.is_null() || !var.is_valid())
			return;

		if (j.is_array())
			load_array(var, j);
		else if (j.is_boolean())
			load_boolean(var, j);
		else if (j.is_number())
			load_number(var, j);
		else if (j.is_object())
			load_object(var, j);
		else if (j.is_string())
			load_string(var, j);
	}

	void serializer::save_arithmetic(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		if (var.is_type<bool>())
		{
			if (!j.is_array()) j = var.get_value<bool>();
			else j.emplace_back(var.get_value<bool>());
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
		else if (var.is_type<wchar_t>())
		{
			if (!j.is_array()) j = var.get_value<wchar_t>();
			else j.emplace_back(var.get_value<wchar_t>());
		}
	}

	void serializer::save_associative_container(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		auto view{ var.create_associative_view() };
		auto j_array{ json::array() };

		for (auto it : view)
		{
			auto j_object{ json::object() };
			save_type(it.first, j_object["key"]);

			if (!view.is_key_only_type())
				save_type(it.second, j_object["value"]);

			j_array.emplace_back(j_object);
		}

		if (!j.is_array()) j = j_array;
		else j.emplace_back(j_array);
	}

	void serializer::save_class(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		for (auto& it : var.get_type().get_properties())
		{
			if ((it.get_specifiers() & specifiers::Serialized) == 0)
				continue;

			save_type(it.get_value(var), j[it.get_name()]);
		}
	}

	void serializer::save_enum(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		if (!j.is_array()) j = std::string(var.get_type().get_enumeration().value_to_name(var)); // TODO conversion string
		else j.emplace_back(std::string(var.get_type().get_enumeration().value_to_name(var))); // TODO conversion string
	}

	void serializer::save_sequential_container(const variant& var, json& j) const REFLECTPP_NOEXCEPT
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
			auto j_array{ json::array() };

			for (auto it : view)
				save_type(it, j_array);

			if (!j.is_array()) j = j_array;
			else j.emplace_back(j_array);
		}
	}

	void serializer::save_type(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		if (!var.is_valid())
			return;

		if (var.get_type().is_arithmetic())
			save_arithmetic(var, j);
		else if (var.is_associative_container())
			save_associative_container(var, j);
		else if (var.get_type().is_class())
			save_class(var, j);
		else if (var.get_type().is_enumeration())
			save_enum(var, j);
		else if (var.is_sequential_container())
			save_sequential_container(var, j);
		else if (var.is_wrapper())
			save_wrapper(var, j);
	}

	void serializer::save_wrapper(const variant& var, json& j) const REFLECTPP_NOEXCEPT
	{
		auto value{ var.create_wrapper_view().get_wrapped_value() };
		auto j_object{ json::object() };

		j_object["type"] = value.get_type().get_name();
		save_type(value, j_object["value"]);

		if (!j.is_array()) j = j_object;
		else j.emplace_back(j_object);
	}
}
