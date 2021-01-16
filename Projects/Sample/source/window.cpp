// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "window.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <type.h>
#include <argument.h>

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
	m_Serializer.load(m_Base);

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

	m_Serializer.save(m_Base);
}

void Window::MenuWindow()
{
	ImGui::Begin("Menu");

	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

	if (ImGui::Button("Save"))
		m_Serializer.save(m_Base);

	ImGui::SameLine();

	if (ImGui::Button("Load"))
		m_Serializer.load(m_Base);

	ImGui::ColorEdit3("clear color", (float*)&m_ClearColor);

	ImGui::EndChild();
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void Window::InspectorWindow()
{
	ImGui::Begin("Inspector");

	if (ImGui::TreeNodeEx("Base", ImGuiTreeNodeFlags_DefaultOpen))
	{
		DisplayType(m_Base);
		ImGui::TreePop();
	}

	ImGui::End();
}

void Window::DisplayType(const reflectpp::variant& var)
{
	for (property prop : var.get_type().get_properties())
	{
		if ((prop.get_specifiers() & specifiers::Exposed) == 0)
			continue;

		variant pvar{ prop.get_value(var) };

		if (pvar.is_type<int>())
			DisplayInt(var, prop, pvar);
		else if (pvar.is_type<unsigned>())
			DisplayUnsigned(var, prop, pvar);
		else if (pvar.is_type<float>())
			DisplayFloat(var, prop, pvar);
		else if (pvar.is_type<double>())
			DisplayFloat(var, prop, pvar);
		else if (ImGui::TreeNodeEx(prop.get_name(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			DisplayType(pvar);
			ImGui::TreePop();
		}
	}
}

void Window::DisplayInt(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	int value = var.get_value<int>();

	if (ImGui::DragInt(prop.get_name(), &value))
		prop.set_value(instance, value);
}

void Window::DisplayUnsigned(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	unsigned value = var.get_value<unsigned>();

	if (ImGui::DragInt(prop.get_name(), (int*)&value))
		prop.set_value(instance, value);
}

void Window::DisplayFloat(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	float value = var.get_value<float>();

	if (ImGui::DragFloat(prop.get_name(), &value))
		prop.set_value(instance, value);
}

void Window::DisplayDouble(const reflectpp::instance& instance, const reflectpp::property& prop, const reflectpp::variant& var)
{
	double value = var.get_value<double>();

	if (ImGui::DragFloat(prop.get_name(), (float*)&value))
		prop.set_value(instance, value);
}

/*
void Window::SampleWindow()
{
	ImGui::Begin("Another Window");
	ImGui::Text("Hello from another window!");
	if (ImGui::Button("Close Me"))
		int i;
	ImGui::End();

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}*/
