#include "Enemy.h"
#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../renderer/Camera.h"
#include "../GameManager.h"

Enemy::Enemy(glm::vec3 position)
{
	name_ = "Enemy";

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
		position,
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
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}
