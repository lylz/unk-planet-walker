#include "Player.h"

#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../application/InputManager.h"
#include "../../renderer/Camera.h"
#include "../GameManager.h"
#include "../Utils.h"

#include <glm/gtc/matrix_transform.hpp>

Player::Player(glm::vec2 position)
{
	name_ = "Player";
    render_type_ = RenderType::DYNAMIC;
    position_ = position;

	Shader *shader = ShaderManager::GetInstance().Get("DynamicObject");
	
	if (shader == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required shader resource!\n");
	}

	Texture *texture = TextureManager::GetInstance().Get("PlanetWalker");

	if (texture == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required texture resource!\n");
	}

	float scale = 0.125f;
	material_ = new DynamicObjectMaterial(shader, texture);
	mesh_ = MeshFactory::CreateQuad(
		{ texture->width() * scale,	texture->height() * scale },
		glm::vec3(0),
		material_
	);
}

Player::~Player()
{
	delete mesh_;
	delete material_;
}

void Player::OnUpdate()
{
	Update();

	glm::vec3 position = CalculateInWorldPositionFromMapPosition(position_);

	material_->SetModelMatrix(glm::translate(glm::mat4(1), position));
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}

void Player::Update()
{
	if (
		move_start_time_ > 0 &&
		move_timer_.start_time() + move_timer_.GetElapsedTime() - move_start_time_ < 150.0f
	)
	{
		// delaying movement
		return;
	}
	else
	{
		move_start_time_ = 0;
	}

	if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_W))
	{
		Move({ 0, 1 });
	}
	else if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_S))
	{
		Move({ 0, -1 });
	}
	else if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_A))
	{
		Move({ -1, 0 });
	}
	else if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_D))
	{
		Move({ 1, 0 });
	}
}

void Player::Move(glm::vec2 step)
{
	move_start_time_ = move_timer_.GetCurrentTime();
	Level *level = GameManager::GetInstance().level();
	assert(level != nullptr);

	glm::vec2 desirable_position = position_ + step;
    std::vector<GameObject *> game_objects = level->GetGameObjectsAtPosition(desirable_position);
    bool can_move = true;

    for (auto game_object: game_objects)
    {
        assert(game_object != nullptr);

        if (game_object->name() == "Wall" || game_object->name() == "Enemy")
        {
            can_move = false;
            break;
        }
    }

    if (can_move)
    {
        position_ = desirable_position;
        GameManager::GetInstance().DescreasePlayerStats();


        for (auto game_object : game_objects)
        {
            // TODO: exit logic
            if (game_object->name() == "OxygenCan")
            {
                GameManager::GetInstance().ConsumeOxygenCan();
                level->DestroyGameObjectById(game_object->id());
            }
            else if (game_object->name() == "HealthPouch")
            {
                GameManager::GetInstance().ConsumeHealthPouch();
                level->DestroyGameObjectById(game_object->id());
            }
        }
    }

    GameObject *enemy = level->GetGameObjectByName("Enemy");

    if (enemy != nullptr)
    {
        dynamic_cast<Enemy *>(enemy)->TakeTurn();
    }
}
