#include "Window.h"
#include "InputManager.h"

Window::Window(const char *title, int width, int height)
{
	if (!glfwInit())
	{
		printf("ERROR: failed to initialize GLFW. \n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window_)
	{
		printf("ERROR: failed to open GLFW window.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window_);
	glfwSetWindowUserPointer(window_, this);
	glfwSetFramebufferSizeCallback(window_, ResizeCallback);
	glfwSetKeyCallback(window_, KeyCallback);
}

void Window::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(window_);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window_) == 1;
}

void Window::ResizeCallback(GLFWwindow *window, int width, int height)
{
	// TODO: glViewport(0, 0, width, height);
	// TODO: recalculate projection matrix
}

void Window::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	InputManager::GetInstance().SetKeyState(key, action);
}

Window::~Window()
{
	glfwDestroyWindow(window_);
	glfwTerminate();
}
