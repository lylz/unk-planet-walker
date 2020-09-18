#pragma once

#include "src/application/Layer.h"
#include "src/renderer/BatchRenderer.h"
#include "src/renderer/MeshFactory.h"
#include "src/renderer/materials/default/UIMaterial.h"
#include "src/renderer/materials/default/TextureHolderMaterial.h"
#include "src/renderer/Camera.h"
#include "src/application/InputManager.h"
#include "src/renderer/font/FontLoader.h"
#include "src/renderer/ui/Text.h"

class UILayer : public Layer
{
private:
	BatchRenderer *renderer_;

	Shader *shader_;
	UIMaterial *material_;

	Text *text_;

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
		Font font = FontLoader::Load("assets/fonts/m6x11.ttf");
		text_ = new Text("Hey, Jimmy, grghh...", font);

		shader_ = Shader::CreateFromFiles("src/renderer/shaders/default/ui.vert", "src/renderer/shaders/default/ui.frag");
		material_ = new UIMaterial(shader_);
		renderer_ = new BatchRenderer(material_);

		for (auto mesh : text_->meshes())
		{
			renderer_->Submit(mesh);
		}
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
