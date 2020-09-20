#include "OxygenCan.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"

OxygenCan::OxygenCan(glm::vec3 position)
{
	Texture *texture = TextureManager::GetInstance().Get("OxygenCan");
	
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

OxygenCan::~OxygenCan()
{
	delete mesh_;
	delete material_;
}
