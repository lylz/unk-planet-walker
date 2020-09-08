#pragma once

#include "src/application/Layer.h"
#include "src/renderer/BatchRenderer.h"
#include "src/renderer/RenderableFactory.h"
#include "src/renderer/materials/default/UIMaterial.h"
#include "src/renderer/materials/default/TextureHolderMaterial.h"
#include "src/application/InputManager.h"

class UILayer : public Layer
{
private:
	BatchRenderer *renderer_;

	Shader *shader_;
	UIMaterial *material_;

	std::vector<Renderable*> renderables_;

	Texture *h_texture_;
	Texture *o_texture_;
	TextureHolderMaterial *h_material_;
	TextureHolderMaterial *o_material_;
	Renderable *h_renderable_;
	Renderable *o_renderable_;

public:
	~UILayer()
	{
		delete renderer_;
		delete material_;
		delete shader_;
	}

	void Init()
	{
		SetVisible(true);
		shader_ = Shader::CreateFromFiles("src/renderer/shaders/default/ui.vert", "src/renderer/shaders/default/ui.frag");
		material_ = new UIMaterial(shader_);
		renderer_ = new BatchRenderer(material_);

		h_texture_ = new Texture("assets/H.png");
		o_texture_ = new Texture("assets/O.png");

		h_material_ = new TextureHolderMaterial(h_texture_);
		o_material_ = new TextureHolderMaterial(o_texture_);

		float scale = 0.005;

		h_renderable_ = RenderableFactory::CreateQuad(
			h_texture_->width() * scale,
			h_texture_->height() * scale,
			{ -10, 0 },
			h_material_
		);
		o_renderable_ = RenderableFactory::CreateQuad(
			o_texture_->width() * scale,
			o_texture_->height() * scale,
			{ -10, 0 },
			o_material_
		);

		renderer_->Submit(h_renderable_);
		renderer_->Submit(o_renderable_);
	}

	void OnUpdate()
	{
		if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_U))
		{
			SetVisible(!visible_);
		}
	}

	void OnRender()
	{
		renderer_->Render();
	}
};
