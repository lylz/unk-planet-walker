#include "Wall.h"

#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../application/InputManager.h"

Wall::Wall(WallType type, glm::vec3 position)
{
	const char *texture_name;

	switch (type)
	{
	case WallType::LEFT_SIDE:
		texture_name = "WallSide";
		break;
	case WallType::RIGHT_SIDE:
		texture_name = "WallSide";
		break;
	case WallType::TOPDOWN:
	default:
		texture_name = "Wall";
	}

	Texture *texture = TextureManager::GetInstance().Get(texture_name);

	if (texture == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required texture resource!\n");
	}

	float scale = 0.125f;
	material_ = new TextureHolderMaterial(texture);
	mesh_ = MeshFactory::CreateQuad(
		texture->width() * scale,
		texture->height() * scale,
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

