#pragma once

#include <map>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	static InputManager &GetInstance()
	{
		static InputManager instance;

		return instance;
	}

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

private:
	InputManager() {};

	std::map<int, int> keys_;

public:
	int GetKeyState(int key_code)
	{
		return keys_[key_code];
	}

	bool GetKeyDown(int key_code)
	{
		int state = keys_[key_code];

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	void SetKeyState(int key_code, int key_state)
	{
		keys_[key_code] = key_state;
	}
};
