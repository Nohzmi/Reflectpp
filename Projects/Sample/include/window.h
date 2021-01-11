// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file window.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <imgui/imgui.h>
#include <property.h>
#include <serializer.h>
#include <variant.h>

#include "base.h"
#include "derived.h"
#include "intern.h"

struct GLFWwindow;

class Window
{
public:

	Window();
	~Window();
	Window(const Window&) = delete;
	Window(Window&&) noexcept = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) noexcept = delete;

	void Update() noexcept;

private:

	void MenuWindow();
	void InspectorWindow();

	void DisplayType(const reflectpp::variant& var);
	void DisplayInt(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayUnsigned(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayFloat(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayDouble(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var);

	GLFWwindow* m_Window{ nullptr };
	ImVec4 m_ClearColor{ ImVec4(0.2f, 0.3f, 0.3f, 1.0f) };

	reflectpp::serializer m_Serializer{ "sample" };
	Base m_Base{ };
};
