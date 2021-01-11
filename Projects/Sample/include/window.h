// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file window.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

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

	void DisplaySampleWindow();

	GLFWwindow* m_Window{ nullptr };
};
