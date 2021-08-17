#include "OxygenCan.h"

#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/Camera.h"
#include "../Utils.h"

OxygenCan::OxygenCan(glm::vec2 position)
{
	name_ = "OxygenCan";
    render_type_ = RenderType::DYNAMIC;
    position_ = position;

    Shader *shader = ShaderManager::GetInstance().Get("DynamicObject");

	if (shader == nullptr)
	{
		throw std::runtime_error("ERROR: Enemy cannot aquare required shader resource!\n");
	}

	Texture *texture = TextureManager::GetInstance().Get("OxygenCan");
	assert(texture != nullptr);

	float scale = 0.125f;
	material_ = new DynamicObjectMaterial(shader, texture);
	mesh_ = MeshFactory::CreateQuad(
        { texture->width() * scale, texture->height() * scale },
		glm::vec3(0),
		material_
	);
}

void OxygenCan::OnUpdate()
{
	glm::vec3 position = CalculateInWorldPositionFromMapPosition(position_);

	material_->SetModelMatrix(glm::translate(glm::mat4(1), position));
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}

OxygenCan::~OxygenCan()
{
	delete material_;
}
