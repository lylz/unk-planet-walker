#include "Passage.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

Passage::Passage(PassageType type, glm::vec3 position)
{
	name_ = "Passage";

	Texture *texture = TextureManager::GetInstance().Get("MapAtlas");
	assert(texture != nullptr);
	SpriteInfo sprite_info = texture->GetSpriteInfo("Passage");

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		sprite_info.size * scale,
		sprite_info.uv,
		position,
		material_
	);
}

Passage::~Passage()
{
	delete mesh_;
	delete material_;
}

void Passage::OnUpdate()
{
}
