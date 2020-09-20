#pragma once

#include "src/application/Layer.h"
#include "src/renderer/BatchRenderer.h"
#include "src/renderer/MeshFactory.h"
#include "src/renderer/materials/default/StaticObjectsMaterial.h"
#include "src/renderer/materials/default/TextureHolderMaterial.h"
#include "src/renderer/Camera.h"
#include "src/renderer/TextureManager.h"
#include "src/application/InputManager.h"
#include "src/game/Level.h"

class MapLayer : public Layer
{
private:
	BatchRenderer *renderer_;

	Shader *shader_;
	StaticObjectsMaterial *material_;

	Level *level_;

public:
	~MapLayer()
	{
		delete renderer_;
		delete material_;
		delete shader_;
	}

	void Init()
	{
		SetVisible(true);

		shader_ = Shader::CreateFromFiles("StaticObject", "src/renderer/shaders/default/static_object.vert", "src/renderer/shaders/default/static_object.frag");
		material_ = new StaticObjectsMaterial(shader_);
		renderer_ = new BatchRenderer(material_);

		TextureManager::GetInstance().Add(new Texture("Wall", "assets/Wall.png"));
		TextureManager::GetInstance().Add(new Texture("WallSide", "assets/WallSide.png"));
		TextureManager::GetInstance().Add(new Texture("Passage", "assets/Passage.png"));
		TextureManager::GetInstance().Add(new Texture("OxygenCan", "assets/OxygenCan.png"));
		TextureManager::GetInstance().Add(new Texture("HealthPouch", "assets/HealthPouch.png"));
		TextureManager::GetInstance().Add(new Texture("Enemy", "assets/Enemy.png"));

		level_ = new Level(10);

		std::vector<GameObject *> game_objects = level_->game_objects();

		for (auto game_object : game_objects)
		{
			renderer_->Submit(game_object->mesh());
		}
	}

	void OnUpdate()
	{
		material_->SetViewMatrix(Camera::GetInstance().view_matrix());
		material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
	}

	void OnRender()
	{
		renderer_->Render();
	}
};
