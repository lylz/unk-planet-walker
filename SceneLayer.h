#pragma once

#include "src/application/Layer.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/Camera.h"
#include "src/application/InputManager.h"
#include "src/renderer/shaders/ShaderManager.h"
#include "src/renderer/TextureManager.h"
#include "src/game/GameObject.h"
#include "src/game/game-objects/Player.h"
#include "src/game/game-objects/Wall.h"

class SceneLayer : public Layer
{
private:
	Renderer *renderer_;

	std::vector<GameObject*> game_objects_;

public:
	SceneLayer()
	{
		renderer_ = nullptr;
		visible_ = true;
		Camera::GetInstance().position.z = 120;
	};

	~SceneLayer()
	{
		for (unsigned int i = 0; i < game_objects_.size(); i++)
		{
			delete game_objects_[i];
		}
	}

	void Init()
	{
		SetVisible(true);
		renderer_ = new Renderer;

		Shader *dynamic_object_shader = Shader::CreateFromFiles("DynamicObject", "src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
		Texture *planet_walker_texture = new Texture("PlanetWalker", "assets/PlanetWalker.png");
		Texture *wall_texture = new Texture("Wall", "assets/Wall.png");

		ShaderManager::GetInstance().Add(dynamic_object_shader);
		TextureManager::GetInstance().Add(planet_walker_texture);
		TextureManager::GetInstance().Add(wall_texture);

		Player *player = new Player();
		Wall *wall = new Wall();

		game_objects_.push_back(wall);
		game_objects_.push_back(player);

		for (GameObject *game_object : game_objects_)
		{
			renderer_->Submit(game_object->mesh());
		}
	};

	void OnUpdate()
	{
		for (GameObject *game_object : game_objects_)
		{
			game_object->OnUpdate();
		}
	};

	void OnRender()
	{
		renderer_->Prepare();
		renderer_->Render();
	};

};
