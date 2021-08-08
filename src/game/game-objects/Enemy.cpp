#include "Enemy.h"
#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../renderer/Camera.h"
#include "../GameManager.h"
#include "../Utils.h"

Enemy::Enemy(glm::vec2 position)
{
	name_ = "Enemy";
    render_type_ = RenderType::DYNAMIC;
    position_ = position;

	Shader *shader = ShaderManager::GetInstance().Get("DynamicObject");

	if (shader == nullptr)
	{
		throw std::runtime_error("ERROR: Enemy cannot aquare required shader resource!\n");
	}

	Texture *texture = TextureManager::GetInstance().Get("Enemy");

	assert(texture != nullptr);

	float scale = 0.125f;
	material_ = new DynamicObjectMaterial(shader, texture);
	mesh_ = MeshFactory::CreateQuad(
		{ texture->width() * scale, texture->height() * scale },
		glm::vec3(0),
		material_
	);
}

Enemy::~Enemy()
{
	delete mesh_;
	delete material_;
}

void Enemy::OnUpdate()
{
	glm::vec3 position = CalculateInWorldPositionFromMapPosition(position_);

	material_->SetModelMatrix(glm::translate(glm::mat4(1), position));
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}

void Enemy::TakeTurn()
{
	ObserveSurroundings();
}

void Enemy::ObserveSurroundings()
{
	Level *level = GameManager::GetInstance().level();
	assert(level != nullptr);

    GameObject *player = level->GetGameObjectByName("Player");
    assert(player != nullptr);

	for (auto observe_direction : ObserveDirections)
	{
		int x = position_.x + observe_direction.x;
		int y = position_.y + observe_direction.y;

		if (x * y <= 0 || x >= level->map_size() || y >= level->map_size())
		{
			continue;
		}

        if (player->position() != glm::vec2({ x, y }))
        {
            continue;
        }

        glm::vec2 position_delta = player->position() - position_;
        glm::vec2 step = { 0, 0 };

        if (glm::abs(position_delta.x) >= glm::abs(position_delta.y))
        {
            step = glm::vec2(1, 0) * glm::sign(position_delta.x);
        }
        else
        {
            step = glm::vec2(0, 1) * glm::sign(position_delta.y);
        }

        glm::vec2 next_position = position_ + step;
        bool can_move = true;

        std::vector<GameObject *> obstacles = level->GetGameObjectsAtPosition(next_position);

        for (auto obstacle : obstacles)
        {
            // TODO: check if the Player is behind the obstacle, if so, Enemy might not see him
            // but if we deside that Enemy can see the Player, then check if we try to step on the obstacle
            if (obstacle->name() == "Player")
            {
                // TODO: attack
            }

            can_move = false;
        }

        if (can_move)
        {
            position_ += step;
        }
	}
}

