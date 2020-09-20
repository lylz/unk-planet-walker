#include "HealthPouch.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

HealthPouch::HealthPouch(glm::vec3 position)
{
	Texture *texture = TextureManager::GetInstance().Get("HealthPouch");

	assert(texture != nullptr);

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		texture->width() * scale,
		texture->height() * scale,
		position,
		material_
	);
}

HealthPouch::~HealthPouch()
{
	delete mesh_;
	delete material_;
}
