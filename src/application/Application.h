#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "../utils/GLIncludes.h"
#include "ApplicationSettings.h"
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
    ApplicationSettings *application_settings();

private:
	std::string name_;
	int width_;
	int height_;

	Window *window_;
	std::vector<Layer*> layers_;

    ApplicationSettings *application_settings_;

	void MainLoop();

protected:
	void Init();
	void Update(long double dt);
	void Render();

	virtual void OnInit() = 0;
};

