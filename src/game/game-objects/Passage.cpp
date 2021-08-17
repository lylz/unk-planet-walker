#include "Passage.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../Utils.h"

Passage::Passage(PassageType type, glm::vec2 position)
{
	name_ = "Passage";
    render_type_ = RenderType::STATIC;
    position_ = position;

	Texture *texture = TextureManager::GetInstance().Get("MapAtlas");
	assert(texture != nullptr);
	SpriteInfo sprite_info = texture->GetSpriteInfo("Passage");

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		sprite_info.size * scale,
		sprite_info.uv,
		CalculateInWorldPositionFromMapPosition(position_),
		material_
	);
}

Passage::~Passage()
{
	delete material_;
}

void Passage::OnUpdate()
{
}
