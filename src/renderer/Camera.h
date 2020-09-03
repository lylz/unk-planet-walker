#pragma once

#include "glm/glm.hpp"
#define GLM_FORCE_RADIANS
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
public:
	static Camera &GetInstance()
	{
		static Camera instance;

		return instance;
	}

	Camera(Camera const&) = delete;
	void operator=(Camera const&) = delete;

	glm::vec3 position;

	glm::vec3 look_at()
	{
		return glm::vec3(position.x, position.y, 0);
	}

private:
	Camera()
	{
		position = glm::vec3(0.0f, 0.0f, 30.0f);
		projection_matrix_ = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f); // TODO: get aspect ration from the window
	};

	glm::mat4 projection_matrix_;

public:
	inline glm::mat4 projection_matrix() { return projection_matrix_; }

	glm::mat4 view_matrix()
	{
		return glm::lookAt(position, look_at(), { 0.0f, 1.0f, 0.0 });
	}
};

