// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file window.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <imgui/imgui.h>
#include <reflectpp.h>
#include <vector>

#include "component.h"
#include "example.h"
#include "transform.h"

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
	void DisplayBool(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayInt(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayFloat(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayEnum(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	void DisplayString(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var);
	std::string GetLabel(const char* label) const;

	GLFWwindow* m_Window{ nullptr };
	ImVec4 m_ClearColor{ ImVec4(0.2f, 0.3f, 0.3f, 1.0f) };
	int m_Index{ 0 };

	reflectpp::serializer m_Serializer{ "sample" };
	std::vector<std::unique_ptr<Component>> m_Components;
};
