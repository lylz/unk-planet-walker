#include "Renderer.h"

Renderer::Renderer()
{
	default_shader_ = Shader::CreateFromFiles("src/renderer/shaders/default/default.vert", "src/renderer/shaders/default/default.frag");
}

Renderer::~Renderer()
{
	delete default_shader_;
}

void Renderer::Prepare()
{
	// glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Render(std::vector<Renderable2D*> renderable_objects)
{
	assert(default_shader_ != nullptr);

	for (Renderable2D *renderable_object : renderable_objects)
	{
		Material *material = renderable_object->material();

		if (material != nullptr)
		{
			material->Bind();
		}
		else
		{
			default_shader_->Use();
		}

		renderable_object->Prepare();
		renderable_object->Draw();

		if (material != nullptr)
		{
			material->Unbind();
		}
	}
}
