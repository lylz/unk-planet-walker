#include "Enemy.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

Enemy::Enemy(glm::vec3 position)
{
	Texture *texture = TextureManager::GetInstance().Get("Enemy");

	assert(texture != nullptr);

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
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

}
