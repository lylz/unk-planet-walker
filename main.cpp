#include <stdio.h>
#include <chrono>

#include "src/utils/GLIncludes.h" // wierd hackish stuff should be included first in the app to prevent an dependency error about gl.h
#include "src/Window.h"
#include "src/InputManager.h"
#include "src/renderer/Renderable2D.h"
#include "src/renderer/Renderer.h"
#include "src/renderer/materials/default/DynamicObjectMaterial.h"
#include "src/renderer/Camera.h"

int main()
{
	Window window("Unk Planet Walker", 1024, 720);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		printf("ERROR: unable initialize glew. \n");
		exit(EXIT_FAILURE);
	}

	Shader *dynamic_object = Shader::CreateFromFiles("src/renderer/shaders/default/dynamic_object.vert", "src/renderer/shaders/default/dynamic_object.frag");
	DynamicObjectMaterial *dynamic_object_material = new DynamicObjectMaterial(dynamic_object);
	Renderable2D cube(dynamic_object_material);
	Renderer renderer;

	float speed = 0.05f;
	const glm::mat4 original_model_matrix = glm::mat4(1);
	glm::vec3 position = glm::vec3(0);

	Camera::GetInstance().position.z = 5.0f;

	using namespace std::chrono;

	int updates = 0;
	int frames = 0;
	int fps = 0;
	int ups = 0;

	long double ns = (double) 1000000000 / 30;
	long double previous_time = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
	long double time = duration_cast<nanoseconds>(system_clock::duration::zero()).count();
	milliseconds timer = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	while (!window.ShouldClose())
	{
		window.Update();

		long double current_time = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
		long double frame_time = current_time - previous_time;
		time += frame_time / ns;
		previous_time = current_time;

		//printf("Frame Time: %.4f ms. UPS: %d, FPS: %d\n", (double)frame_time / 1000000, ups, fps);

		if (time >= 1.0)
		{
			if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_W))
			{
				position.y += speed;
			}

			if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_S))
			{
				position.y -= speed;
			}

			if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_A))
			{
				position.x -= speed;
			}

			if (InputManager::GetInstance().GetKeyDown(GLFW_KEY_D))
			{
				position.x += speed;
			}

			dynamic_object_material->SetModelMatrix(glm::translate(original_model_matrix, position));
			dynamic_object_material->SetViewMatrix(Camera::GetInstance().view_matrix());
			dynamic_object_material->SetProjectionMatrix(Camera::GetInstance().projection_matrix());

			updates++;
			time--;
		}

		renderer.Prepare();
		renderer.Render({ &cube });

		frames++;

		if (duration_cast<milliseconds>(system_clock::now().time_since_epoch()) - timer > (milliseconds)1000)
		{
			timer += (milliseconds)1000;

			printf("UPS: %d\n", updates);
			printf("FPS: %d\n", frames);

			ups = updates;
			fps = frames;

			updates = 0;
			frames = 0;
		}
	}

	delete dynamic_object_material;
	delete dynamic_object;

	return 0;
}
