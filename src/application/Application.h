#pragma once

#include <stdio.h>
#include <string>
#include <chrono>

#include "../utils/GLIncludes.h"
#include "Window.h"
#include "../renderer/Renderer.h"
#include "../renderer/BatchRenderer.h"
#include "../renderer/materials/default/UIMaterial.h"

class Application
{
public:
	Application(std::string name, int width, int height);
	~Application();

	void Run();
private:
	std::string name_;
	int width_;
	int height_;

	Window *window_;
	Renderer *renderer_;

	Shader *ui_shader_;
	UIMaterial *ui_material_;
	BatchRenderer *ui_renderer_;

	void MainLoop();

protected:
	virtual void OnUpdate(long double dt) = 0;
	virtual void OnRender(Renderer *renderer) = 0;
	virtual void OnUIUpdate(BatchRenderer *renderer) = 0;
	virtual void OnUIRender(BatchRenderer *renderer) = 0;
};

