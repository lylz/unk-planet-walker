#pragma once

#include "src/application/Layer.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/Camera.h"
#include "src/application/InputManager.h"
#include "src/renderer/shaders/ShaderManager.h"
#include "src/renderer/TextureManager.h"
#include "src/game/GameObject.h"
#include "src/game/game-objects/Player.h"

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
		Camera::GetInstance().position.z = 60;
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

		ShaderManager::GetInstance().Add(Shader::CreateFromFiles("DynamicObject", "src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag"));
		TextureManager::GetInstance().Add(new Texture("PlanetWalker", "assets/PlanetWalker.png"));

		Player *player = new Player();

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
