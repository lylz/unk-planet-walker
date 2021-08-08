#pragma once

#include "../application/InputManager.h"
#include "../application/Layer.h"
#include "../renderer/BatchRenderer.h"
#include "../renderer/MeshFactory.h"
#include "../renderer/materials/default/UIMaterial.h"
#include "../renderer/materials/default/TextureHolderMaterial.h"
#include "../renderer/Camera.h"
#include "../renderer/font/FontLoader.h"
#include "../renderer/font/FontManager.h"
#include "../renderer/ui/Text.h"

class UILayer : public Layer
{
private:
	BatchRenderer *renderer_;

	Shader *shader_;
	UIMaterial *material_;

	PlayerStats last_player_stats_;

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
		Font font = FontLoader::Load("PixelFont", "assets/fonts/m6x11.ttf");
		FontManager::GetInstance().Add(font);
		Text text = Text("UnkPlanetWalker v0.1.0", font);

		shader_ = Shader::CreateFromFiles("UI", "src/renderer/shaders/default/ui.vert", "src/renderer/shaders/default/ui.frag");
		material_ = new UIMaterial(shader_);
		renderer_ = new BatchRenderer(material_);

		for (auto mesh : text.meshes())
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

		PlayerStats *player_stats = GameManager::GetInstance().player_stats();

		// NOTE: last_player_stats_ is used to minimize the time of text updates
		if (
			last_player_stats_.hp != player_stats->hp ||
			last_player_stats_.oxygen != player_stats->oxygen
			)
		{
			std::string stats = "HP: " + std::to_string(player_stats->hp) + " | O2: " + std::to_string(player_stats->oxygen);
			Font font = FontManager::GetInstance().Get("PixelFont");
			Text text = Text(stats, font);

			renderer_->Flush();

			for (auto mesh : text.meshes())
			{
				renderer_->Submit(mesh);
			}

			last_player_stats_ = *player_stats;
		}
	}

	void OnRender()
	{
		renderer_->Render();
	}
};
