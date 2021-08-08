#pragma once

#include "../application/InputManager.h"
#include "../application/Layer.h"
#include "../renderer/Renderer.h"
#include "../renderer/BatchRenderer.h"
#include "../renderer/materials/default/StaticObjectsMaterial.h"
#include "../renderer/materials/default/TextureHolderMaterial.h"
#include "../renderer/Camera.h"
#include "../renderer/shaders/ShaderManager.h"
#include "../renderer/TextureManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "game-objects/Player.h"
#include "game-objects/Enemy.h"

class GameLayer : public Layer
{
private:
	Renderer *renderer_;
	BatchRenderer *batch_renderer_;

	Shader *batch_shader_;
	StaticObjectsMaterial *batch_material_;

public:
	GameLayer()
	{
		renderer_ = nullptr;
		batch_renderer_ = nullptr;
		batch_shader_ = nullptr;
		batch_material_ = nullptr;

		visible_ = true;
		Camera::GetInstance().position.z = 60;
	}

	~GameLayer()
	{
		delete renderer_;
		delete batch_renderer_;
		delete batch_material_;
		delete batch_shader_;
	}

	void Init()
	{
		SetVisible(true);

		batch_shader_ = Shader::CreateFromFiles("StaticObject", "src/renderer/shaders/default/static_object.vert", "src/renderer/shaders/default/static_object.frag");
		batch_material_ = new StaticObjectsMaterial(batch_shader_);
		batch_renderer_ = new BatchRenderer(batch_material_);

		TextureManager::GetInstance().Add(new Texture("MapAtlas", "assets/MapAtlas.png", "assets/MapAtlas.json"));
		
		renderer_ = new Renderer;

		ShaderManager::GetInstance().Add(Shader::CreateFromFiles("DynamicObject", "src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag"));
		TextureManager::GetInstance().Add(new Texture("PlanetWalker", "assets/PlanetWalker.png"));
		TextureManager::GetInstance().Add(new Texture("Enemy", "assets/Enemy.png"));
        TextureManager::GetInstance().Add(new Texture("OxygenCan", "assets/OxygenCan.png"));
        TextureManager::GetInstance().Add(new Texture("HealthPouch", "assets/HealthPouch.png"));

		GameManager::GetInstance().GenerateLevel();
		Level *level = GameManager::GetInstance().level();
		assert(level != nullptr);

        level->SetGameObjectsBeforeDestroyCallback(this, GameObjectsBeforeDestroyCallbackStatic);

		// TODO: get world position of camera using level methods
        // TODO: if the map size will be odd number it will cause an incorrect behaviour
		Camera::GetInstance().position.x = (level->map_size() / 2 * 4.0f) - 2.0f;
		Camera::GetInstance().position.y = (level->map_size() / 2 * 4.0f) - 2.0f;

		batch_renderer_->Flush();
		renderer_->Flush();

		for (auto game_object : level->game_objects())
		{
            switch (game_object->render_type())
            {
            case RenderType::STATIC:
                batch_renderer_->Submit(game_object->mesh());
                break;
            case RenderType::DYNAMIC:
                renderer_->Submit(game_object->mesh());
                break;
            }
		}
	}

    static void GameObjectsBeforeDestroyCallbackStatic(void *context, GameObject *game_object)
    {
        GameLayer *game_layer = static_cast<GameLayer*>(context);

        game_layer->GameObjectsBeforeDestroyCallback(game_object);
    }

    void GameObjectsBeforeDestroyCallback(GameObject *game_object)
    {
        assert(game_object != nullptr);
        renderer_->RemoveMeshById(game_object->mesh()->id());
    }

	void OnUpdate()
	{
		batch_material_->SetViewMatrix(Camera::GetInstance().view_matrix());
		batch_material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
		
		Level *level = GameManager::GetInstance().level();
		for (auto game_object : level->game_objects())
		{
			game_object->OnUpdate();
		}
	}

	void OnRender()
	{
		batch_renderer_->Render();
		renderer_->Prepare();
		renderer_->Render();
	}
};

