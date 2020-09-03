#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const char *title, int width, int height);
	~Window();

	static bool keys[1024];

private:
	GLFWwindow *window_;

public:
	void Update();
	bool ShouldClose();

private:
	static void ResizeCallback(GLFWwindow *window, int width, int height);
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};

