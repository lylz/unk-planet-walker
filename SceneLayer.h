#pragma once

#include "src/application/Layer.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/Mesh.h"
#include "src/renderer/MeshFactory.h"
#include "src/renderer/materials/default/DynamicObjectMaterial.h"
#include "src/renderer/Camera.h"
#include "src/application/InputManager.h"

class SceneLayer : public Layer
{
private:
	Renderer *renderer_;

	std::vector<Shader*> dynamic_object_shaders_;
	std::vector<Texture*> dynamic_object_textures_;
	std::vector<DynamicObjectMaterial*> dynamic_object_materials_;

	std::vector<Mesh*> meshes_;
	glm::vec3 position_;
	float speed_;

public:
	SceneLayer()
	{
		renderer_ = nullptr;
		visible_ = true;
		position_ = glm::vec3(0, 0, 3);
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

		for (auto mesh : meshes_)
		{
			delete mesh;
		}

		dynamic_object_materials_.clear();
		dynamic_object_shaders_.clear();
		dynamic_object_textures_.clear();
		meshes_.clear();
	}

	void Init()
	{
		SetVisible(true);
		renderer_ = new Renderer;

		Shader *dynamic_object = Shader::CreateFromFiles("src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
		Texture *dynamic_object_texture = new Texture("assets/Protagonist.png");
		Texture *dynamic_object_texture1 = new Texture("assets/Rapid.png");
		Texture *dynamic_object_texture2 = new Texture("assets/Protagonist.png");
		DynamicObjectMaterial *dynamic_object_material = new DynamicObjectMaterial(dynamic_object, dynamic_object_texture);
		DynamicObjectMaterial *dynamic_object_material1 = new DynamicObjectMaterial(dynamic_object, dynamic_object_texture1);
		DynamicObjectMaterial *dynamic_object_material2 = new DynamicObjectMaterial(dynamic_object, dynamic_object_texture2);

		float scale = .125f;

		Mesh *mesh = MeshFactory::CreateQuad(
			dynamic_object_texture->width() * scale,
			dynamic_object_texture->height() * scale,
			dynamic_object_material
		);
		Mesh *mesh1 = MeshFactory::CreateQuad(
			dynamic_object_texture1->width() * scale,
			dynamic_object_texture1->height() * scale,
			dynamic_object_material1
		);
		Mesh *mesh2 = MeshFactory::CreateQuad(
			dynamic_object_texture2->width() * scale,
			dynamic_object_texture2->height() * scale,
			dynamic_object_material2
		);

		dynamic_object_shaders_.push_back(dynamic_object);
		dynamic_object_textures_.push_back(dynamic_object_texture);
		dynamic_object_textures_.push_back(dynamic_object_texture1);
		dynamic_object_textures_.push_back(dynamic_object_texture2);
		dynamic_object_materials_.push_back(dynamic_object_material);
		dynamic_object_materials_.push_back(dynamic_object_material1);
		dynamic_object_materials_.push_back(dynamic_object_material2);
		meshes_.push_back(mesh);
		meshes_.push_back(mesh1);
		meshes_.push_back(mesh2);
		renderer_->Submit(mesh);
		renderer_->Submit(mesh1);
		renderer_->Submit(mesh2);
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

		for (size_t i = 0; i < meshes_.size(); i++)
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
		renderer_->Render();
	};

};
