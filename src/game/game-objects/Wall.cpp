#include "Wall.h"

#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/materials/default/DynamicObjectMaterial.h"
#include "../../renderer/MeshFactory.h"
#include "../../application/InputManager.h"
#include "../../renderer/Camera.h"

Wall::Wall()
{
	Shader *shader = ShaderManager::GetInstance().Get("DynamicObject");

	if (shader == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required shader resource!\n");
	}

	Texture *texture = TextureManager::GetInstance().Get("Wall");

	if (texture == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required texture resource!\n");
	}

	float scale = 0.125f;
	material_ = new DynamicObjectMaterial(shader, texture);
	mesh_ = MeshFactory::CreateQuad(
		texture->width() * scale,
		texture->height() * scale,
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
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}

