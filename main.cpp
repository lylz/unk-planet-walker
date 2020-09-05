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
		Camera::GetInstance().position.z = 5.0f;
		position_ = glm::vec3(0);
		speed_ = .05f;

		dynamic_object_ = Shader::CreateFromFiles("src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
		dynamic_object_material_ = new DynamicObjectMaterial(dynamic_object_);

		cube_ = new Renderable2D(dynamic_object_material_);
	};

	~UnkPlanetWalkerApplication()
	{
		delete dynamic_object_material_;
		delete dynamic_object_;
	}

private:
	Shader *dynamic_object_;
	DynamicObjectMaterial *dynamic_object_material_;
	
	Renderable2D *cube_;
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

		dynamic_object_material_->SetModelMatrix(glm::translate(glm::mat4(1), position_));
		dynamic_object_material_->SetViewMatrix(Camera::GetInstance().view_matrix());
		dynamic_object_material_->SetProjectionMatrix(Camera::GetInstance().projection_matrix());
	}

	void OnRender(Renderer *renderer)
	{
		renderer->Prepare();
		renderer->Render({ cube_ });
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
