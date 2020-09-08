#pragma once

#include "src/application/Layer.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/Renderable2D.h"
#include "src/renderer/materials/default/DynamicObjectMaterial.h"
#include "src/renderer/Camera.h"
#include "src/application/InputManager.h"

class SceneLayer : public Layer
{
private:
	Renderer *renderer_;

	std::vector<Shader *> dynamic_object_shaders_;
	std::vector<Texture *> dynamic_object_textures_;
	std::vector<DynamicObjectMaterial *> dynamic_object_materials_;

	std::vector<Renderable2D *> renderables_;
	glm::vec3 position_;
	float speed_;

public:
	SceneLayer()
	{
		renderer_ = nullptr;
		visible_ = true;
		position_ = glm::vec3(0);
		speed_ = .5f;
	};


	~SceneLayer()
	{
		for (auto material : dynamic_object_materials_)
		{
			delete material;
		}

		for (auto shader : dynamic_object_shaders_)
		{
			delete shader;
		}

		for (auto texture : dynamic_object_textures_)
		{
			delete texture;
		}

		for (auto renderable : renderables_)
		{
			delete renderable;
		}

		dynamic_object_materials_.clear();
		dynamic_object_shaders_.clear();
		dynamic_object_textures_.clear();
		renderables_.clear();
	}

	void Init()
	{
		SetVisible(true);
		renderer_ = new Renderer;

		Shader *dynamic_object = Shader::CreateFromFiles("src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
		Texture *dynamic_object_texture = new Texture("assets/Protagonist.png");
		Texture *dynamic_object_texture1 = new Texture("assets/Rapid.png");
		DynamicObjectMaterial *dynamic_object_material = new DynamicObjectMaterial(dynamic_object, dynamic_object_texture);
		DynamicObjectMaterial *dynamic_object_material1 = new DynamicObjectMaterial(dynamic_object, dynamic_object_texture1);
		Renderable2D *renderable = new Renderable2D(dynamic_object_material);
		Renderable2D *renderable1 = new Renderable2D(dynamic_object_material1);

		dynamic_object_shaders_.push_back(dynamic_object);
		dynamic_object_textures_.push_back(dynamic_object_texture);
		dynamic_object_textures_.push_back(dynamic_object_texture1);
		dynamic_object_materials_.push_back(dynamic_object_material);
		dynamic_object_materials_.push_back(dynamic_object_material1);
		renderables_.push_back(renderable);
		renderables_.push_back(renderable1);
	};

	void OnUpdate()
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

		for (size_t i = 0; i < renderables_.size(); i++)
		{
			auto material = dynamic_object_materials_[i];

			if (i == 0)
			{
				material->SetModelMatrix(glm::translate(glm::mat4(1), position_));
			}

			material->SetViewMatrix(Camera::GetInstance().view_matrix());
			material->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
		}
	};

	void OnRender()
	{
		renderer_->Prepare();
		renderer_->Render(renderables_);
	};

};
