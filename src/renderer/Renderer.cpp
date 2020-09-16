#include "Renderer.h"

Renderer::Renderer()
{
	default_shader_ = Shader::CreateFromFiles("src/renderer/shaders/default/default.vert", "src/renderer/shaders/default/default.frag");
}

Renderer::~Renderer()
{
	renderables_.clear();

	delete default_shader_;
}

void Renderer::Submit(Mesh *mesh)
{
	Renderable *renderable = new Renderable(mesh);
	renderables_.push_back(renderable);
}

void Renderer::Prepare()
{
	// glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::Render()
{
	assert(default_shader_ != nullptr);

	for (Renderable *renderable_object : renderables_)
	{
		Material *material = renderable_object->mesh()->material();

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
