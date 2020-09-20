#include "Player.h"

#include "../../renderer/shaders/ShaderManager.h"
#include "../../renderer/TextureManager.h"
#include "../../renderer/MeshFactory.h"
#include "../../application/InputManager.h"
#include "../../renderer/Camera.h"

Player::Player()
{
	Shader *shader = ShaderManager::GetInstance().Get("DynamicObject");
	
	if (shader == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required shader resource!\n");
	}

	Texture *texture = TextureManager::GetInstance().Get("PlanetWalker");

	if (texture == nullptr)
	{
		throw std::runtime_error("ERROR: Player cannot aquare required texture resource!\n");
	}

	float scale = 0.125f;
	material_ = new DynamicObjectMaterial(shader, texture);
	mesh_ = MeshFactory::CreateQuad(
		{ texture->width() * scale,	texture->height() * scale },
		material_
	);

	position_ = glm::vec3(0);
	speed_ = 4.0f;
}

Player::~Player()
{
	delete mesh_;
	delete material_;
}

void Player::OnUpdate()
{
	if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_W))
	{
		position_.y += speed_;
	}

	if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_S))
	{
		position_.y -= speed_;
	}

	if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_A))
	{
		position_.x -= speed_;
	}

	if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_D))
	{
		position_.x += speed_;
	}

	material_->SetModelMatrix(glm::translate(glm::mat4(1), position_));
	material_->SetViewMatrix(Camera::GetInstance().view_matrix());
	material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
}
