#pragma once

#include <stdio.h>
#include <string>
#include <chrono>
#include <vector>

#include "../utils/GLIncludes.h"
#include "Window.h"
#include "Layer.h"

class Application
{
public:
	Application(std::string name, int width, int height);
	~Application();

	void Run();
	void AddLayer(Layer *layer);
	void RemoveLayer(Layer *layer);

private:
	std::string name_;
	int width_;
	int height_;

	Window *window_;
	std::vector<Layer*> layers_;

	void MainLoop();

protected:
	void Init();
	void Update(long double dt);
	void Render();

	virtual void OnInit() = 0;
};

