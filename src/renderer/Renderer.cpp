#include "Renderer.h"

Renderer::Renderer()
{
	shader_ = new Shader();

	shader_->CompileShader("src/renderer/shaders/default/default.vert");
	shader_->CompileShader("src/renderer/shaders/default/default.frag");
	shader_->Link();
	shader_->Validate();
}

Renderer::~Renderer()
{
	delete shader_;
}

void Renderer::Prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Render(std::vector<IRenderable*> renderable_objects)
{
	assert(shader_ != nullptr);

	shader_->Use();

	for (IRenderable *renderable_object : renderable_objects)
	{
		renderable_object->Prepare();
		renderable_object->Draw();
	}
}
