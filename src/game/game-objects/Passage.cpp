#include "Passage.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

Passage::Passage(PassageType type, glm::vec3 position)
{
	Texture *texture = TextureManager::GetInstance().Get("Passage");

	if (texture == nullptr)
	{
		throw std::runtime_error("ERROR: Passage cannot aquare required texture!\n");
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

Passage::~Passage()
{
	delete mesh_;
	delete material_;
}

void Passage::OnUpdate()
{
}
