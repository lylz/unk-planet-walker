#include "HealthPouch.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

HealthPouch::HealthPouch(glm::vec3 position)
{
	Texture *texture = TextureManager::GetInstance().Get("MapAtlas");
	assert(texture != nullptr);
	SpriteInfo sprite_info = texture->GetSpriteInfo("HealthPouch");

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		sprite_info.size * scale,
		sprite_info.uv,
		position,
		material_
	);
}

HealthPouch::~HealthPouch()
{
	delete mesh_;
	delete material_;
}
