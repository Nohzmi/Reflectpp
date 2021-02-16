// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <reflectpp.h>

using namespace reflectpp;

Window::Window()
{
	glfwSetErrorCallback([](int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	});

	if (!glfwInit())
		return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(1280, 720, "Sample", nullptr, nullptr);

	if (m_Window == nullptr)
		return;

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	if (gladLoadGL() == 0)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	ImGui::StyleColorsDark();
}

Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::Update() noexcept
{
	m_Serializer.load(m_Components);

	while (!glfwWindowShouldClose(m_Window))
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		MenuWindow();
		InspectorWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	m_Serializer.save(m_Components);
}

void Window::MenuWindow()
{
	ImGui::Begin("Menu");

	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

	if (ImGui::Button("Save"))
		m_Serializer.save(m_Components);

	ImGui::SameLine();

	if (ImGui::Button("Load"))
		m_Serializer.load(m_Components);

	ImGui::ColorEdit3("clear color", (float*)&m_ClearColor);

	ImGui::EndChild();
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void Window::InspectorWindow()
{
	ImGui::Begin("Inspector");

	if (ImGui::BeginPopup("AddComponentPopup"))
	{
		reflectpp::type base_type{ reflectpp::type::get<Component>() };

		for (auto& it : base_type.get_derived_classes())
		{
			if (ImGui::MenuItem(it.get_name()))
			{
				auto view{ variant(m_Components).create_sequential_view() };
				auto var = reflectpp::type::get<std::unique_ptr<Component>>().create();
				var.create_wrapper_view().reset(it.create());
				view.insert(view.end(), var);
			}
		}

		ImGui::EndPopup();
	}

	m_Index = 0;

	for (auto it = m_Components.begin(); it != m_Components.end(); ++it, ++m_Index)
	{
		ImGui::Separator();

		reflectpp::type type{ reflectpp::type::get(*it) };

		if (ImGui::TreeNodeEx(GetLabel(type.get_name()).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::BeginPopupContextItem("RightClickInspectorOptions"))
			{
				if (ImGui::MenuItem("Remove Component"))
				{
					m_Components.erase(it);
					ImGui::EndPopup();
					ImGui::TreePop();
					break;
				}

				ImGui::EndPopup();
			}

			DisplayType(*it->get());
			ImGui::TreePop();
		}
	}

	ImGui::Separator();

	if (ImGui::Button("Add Component", ImVec2(-1, 0)))
		ImGui::OpenPopup("AddComponentPopup");

	ImGui::End();
}

void Window::DisplayType(const reflectpp::variant& var)
{
	for (property prop : var.get_type().get_properties())
	{
		if ((prop.get_specifiers() & specifiers::Exposed) == 0)
			continue;

		variant pvar{ prop.get_value(var) };

		if (pvar.is_type<bool>())
			DisplayBool(var, prop, pvar);
		else if (pvar.is_type<int>())
			DisplayInt(var, prop, pvar);
		else if (pvar.is_type<float>())
			DisplayFloat(var, prop, pvar);
		else if (pvar.get_type().is_enumeration())
			DisplayEnum(var, prop, pvar);
		else if (pvar.is_type<std::string>())
			DisplayString(var, prop, pvar);
		else if (ImGui::TreeNodeEx(GetLabel(prop.get_name()).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			DisplayType(pvar);
			ImGui::TreePop();
		}
	}
}

void Window::DisplayBool(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	bool value{ var.get_value<bool>() };

	if (ImGui::Checkbox(GetLabel(prop.get_name()).c_str(), &value))
		prop.set_value(instance, value);
}

void Window::DisplayInt(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	int value{ var.get_value<int>() };

	if (ImGui::DragInt(GetLabel(prop.get_name()).c_str(), &value))
		prop.set_value(instance, value);
}

void Window::DisplayFloat(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	float value{ var.get_value<float>() };

	if (ImGui::DragFloat(GetLabel(prop.get_name()).c_str(), &value))
		prop.set_value(instance, value);
}

void Window::DisplayEnum(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	reflectpp::enumeration e{ prop.get_type().get_enumeration() };
	std::vector<std::string> items;

	for (auto& name : e.get_names())
		items.emplace_back(name);

	std::string current_item{ e.value_to_name(var) };

	if (ImGui::BeginCombo(GetLabel(prop.get_name()).c_str(), current_item.c_str()))
	{
		for (auto& item : items)
			if (ImGui::Selectable(item.c_str(), item == current_item))
				prop.set_value(instance, e.name_to_value(item.c_str()));

		ImGui::EndCombo();
	}
}

void Window::DisplayString(const reflectpp::variant& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	char buffer[1000];
	std::memcpy(buffer, var.get_value<std::string>().c_str(), 1000);

	if (ImGui::InputText(GetLabel(prop.get_name()).c_str(), buffer, 1000))
		prop.set_value(instance, std::string(buffer));
}

std::string Window::GetLabel(const char* label) const
{
	return std::string(label) + std::string("##") + std::to_string(m_Index);
}
