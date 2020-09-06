#include <stdio.h>
#include <chrono>

#include "src/utils/GLIncludes.h" // wierd hackish stuff should be included first in the app to prevent an dependency error about gl.h
#include "src/application/Application.h"
#include "src/application/InputManager.h"
#include "src/renderer/Renderable2D.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/materials/default/DynamicObjectMaterial.h"
#include "src/renderer/Camera.h"

class UnkPlanetWalkerApplication : public Application
{
public:
	UnkPlanetWalkerApplication(std::string name, int width, int height)
		: Application(name, width, height)
	{
		position_ = glm::vec3(0);
		speed_ = .5f;

		dynamic_object_ = Shader::CreateFromFiles("src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
		Texture *dynamic_object_texture = new Texture("assets/Protagonist.png");
		Texture *dynamic_object_texture1 = new Texture("assets/Rapid.png");
		DynamicObjectMaterial *dynamic_object_material = new DynamicObjectMaterial(dynamic_object_, dynamic_object_texture);
		DynamicObjectMaterial *dynamic_object_material1 = new DynamicObjectMaterial(dynamic_object_, dynamic_object_texture1);
		Renderable2D *renderable = new Renderable2D(dynamic_object_material);
		Renderable2D *renderable1 = new Renderable2D(dynamic_object_material1);

		dynamic_object_textures_.push_back(dynamic_object_texture);
		dynamic_object_textures_.push_back(dynamic_object_texture1);
		dynamic_object_materials_.push_back(dynamic_object_material);
		dynamic_object_materials_.push_back(dynamic_object_material1);
		renderables_.push_back(renderable);
		renderables_.push_back(renderable1);
	};

	~UnkPlanetWalkerApplication()
	{
		for (auto material : dynamic_object_materials_)
		{
			delete material;
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
		dynamic_object_textures_.clear();
		renderables_.clear();
		delete dynamic_object_;
	}

private:
	Shader *dynamic_object_;
	std::vector<Texture*> dynamic_object_textures_;
	std::vector<DynamicObjectMaterial*> dynamic_object_materials_;
	
	std::vector<Renderable2D*> renderables_;
	glm::vec3 position_;
	float speed_;

protected:
	void OnUpdate(long double dt)
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
	}

	void OnRender(Renderer *renderer)
	{
		std::vector<IRenderable*> renderables;

		for (auto renderable : renderables_)
		{
			renderables.push_back(renderable);
		}

		renderer->Prepare();
		renderer->Render(renderables);
	}
};

int main()
{
	try
	{
		UnkPlanetWalkerApplication app("Unk Planet Walker", 1024, 720);

		app.Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
