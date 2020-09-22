#pragma once

#include "../application/InputManager.h"
#include "../application/Layer.h"
#include "../renderer/BatchRenderer.h"
#include "../renderer/MeshFactory.h"
#include "../renderer/materials/default/StaticObjectsMaterial.h"
#include "../renderer/materials/default/TextureHolderMaterial.h"
#include "../renderer/Camera.h"
#include "../renderer/TextureManager.h"
#include "GameManager.h"
#include "game-objects/Enemy.h"
#include "game-objects/HealthPouch.h"
#include "game-objects/OxygenCan.h"
#include "game-objects/Passage.h"
#include "game-objects/Wall.h"

class MapLayer : public Layer
{
private:
	BatchRenderer *renderer_;

	Shader *shader_;
	StaticObjectsMaterial *material_;

	std::vector<GameObject *> game_objects_;

public:
	~MapLayer()
	{
		FlushGameObjects();

		delete renderer_;
		delete material_;
		delete shader_;
	}

	void FlushGameObjects()
	{
		for (unsigned int i = 0; i < game_objects_.size(); i++)
		{
			delete game_objects_[i];
		}

		game_objects_.clear();
	}

	void Init()
	{
		SetVisible(true);

		shader_ = Shader::CreateFromFiles("StaticObject", "src/renderer/shaders/default/static_object.vert", "src/renderer/shaders/default/static_object.frag");
		material_ = new StaticObjectsMaterial(shader_);
		renderer_ = new BatchRenderer(material_);

		TextureManager::GetInstance().Add(new Texture("Enemy", "assets/Enemy.png"));
		TextureManager::GetInstance().Add(new Texture("MapAtlas", "assets/MapAtlas.png", "assets/MapAtlas.json"));

		MakeGameObjectsFromLevel();
	}

	void MakeGameObjectsFromLevel()
	{
		Level *level = GameManager::GetInstance().level();
		if (level == nullptr)
		{
			return;
		}

		FlushGameObjects();
		auto map = level->map();

		float half_map_point = 4 * (map.size() / 2);
		glm::vec2 top_left = glm::vec2(-half_map_point, half_map_point);

		for (unsigned int i = 0; i < map.size(); i++)
		{
			for (unsigned int j = 0; j < map[i].size(); j++)
			{
				glm::vec2 position = top_left + glm::vec2(i * 4.0f, j * -4.0f);

				switch (map[i][j])
				{
				case MapEntry::OBSTACLE:
					game_objects_.push_back(new Wall(WallType::TOPDOWN, glm::vec3(position, 0)));
					break;
				case MapEntry::ENTRANCE:
					game_objects_.push_back(new Passage(PassageType::ENTRANCE, glm::vec3(position, 0)));
					break;
				case MapEntry::EXIT:
					game_objects_.push_back(new Passage(PassageType::EXIT, glm::vec3(position, 0)));
					break;
				case MapEntry::OXYGEN_CAN:
					game_objects_.push_back(new OxygenCan(glm::vec3(position, 0)));
					break;
				case MapEntry::HEALTH_POUCH:
					game_objects_.push_back(new HealthPouch(glm::vec3(position, 0)));
					break;
				case MapEntry::ENEMY:
					game_objects_.push_back(new Enemy(glm::vec3(position, 0)));
					break;
				case MapEntry::WALL:
					if (i == 0 || i == map.size() - 1)
					{
						game_objects_.push_back(new Wall(WallType::LEFT_SIDE, glm::vec3(position, 0)));
					}
					else if (j == 0 || j == map.size() - 1) {
						game_objects_.push_back(new Wall(WallType::TOPDOWN, glm::vec3(position, 0)));
					}
					break;
				}
			}
		}

		renderer_->Flush();
		for (auto game_object : game_objects_)
		{
			renderer_->Submit(game_object->mesh());
		}
	}

	void OnUpdate()
	{
		if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_R))
		{
			GameManager::GetInstance().GenerateLevel();
			MakeGameObjectsFromLevel();
		}

		material_->SetViewMatrix(Camera::GetInstance().view_matrix());
		material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
	}

	void OnRender()
	{
		renderer_->Render();
	}
};
