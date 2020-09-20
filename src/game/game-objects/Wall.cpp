#include "Wall.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

Wall::Wall(WallType type, glm::vec3 position)
{
	const char *sprite_name;

	switch (type)
	{
	case WallType::LEFT_SIDE:
		sprite_name = "WallSide";
		break;
	case WallType::RIGHT_SIDE:
		sprite_name = "WallSide";
		break;
	case WallType::TOPDOWN:
	default:
		sprite_name = "Wall";
	}

	Texture *texture = TextureManager::GetInstance().Get("MapAtlas");
	assert(texture != nullptr);
	SpriteInfo sprite_info = texture->GetSpriteInfo(sprite_name);

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		sprite_info.size * scale,
		sprite_info.uv,
		position,
		material_
	);
}

Wall::~Wall()
{
	delete mesh_;
	delete material_;
}

void Wall::OnUpdate()
{
}

