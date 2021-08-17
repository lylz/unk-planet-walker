#include "Renderer.h"

Renderer::Renderer()
{
	default_shader_ = Shader::CreateFromFiles("INTERNAL_Default", "src/renderer/shaders/default/default.vert", "src/renderer/shaders/default/default.frag");
}

Renderer::~Renderer()
{
	Flush();

	delete default_shader_;
}

void Renderer::Submit(Mesh *mesh)
{
	Renderable renderable = Renderable(mesh);
	renderables_.push_back(renderable);
}

void Renderer::RemoveMeshById(unsigned int id)
{
    for (unsigned int i = 0; i < renderables_.size(); i++)
    {
        Renderable *renderable = &renderables_[i];

        if (renderable->mesh()->id() == id)
        {
            renderables_.erase(renderables_.begin() + i);
            break;
        }
    }
}

void Renderer::Flush()
{
	renderables_.clear();
}

void Renderer::Prepare()
{
	// glEnable(GL_DEPTH_TEST);
	GLWCall(glEnable(GL_BLEND));
	GLWCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::Render()
{
	assert(default_shader_ != nullptr);

	for (Renderable &renderable_object : renderables_)
	{
		Material *material = renderable_object.mesh()->material();

		if (material != nullptr)
		{
			material->Bind();
		}
		else
		{
			default_shader_->Use();
		}

		renderable_object.Prepare();
		renderable_object.Draw();

		if (material != nullptr)
		{
			material->Unbind();
		}
	}
}
