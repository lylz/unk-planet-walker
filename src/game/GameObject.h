#pragma once

#include "../utils/IdentifierManager.h"
#include "../renderer/Mesh.h"

enum class RenderType
{
    STATIC,
    DYNAMIC
};

class GameObject
{
public:
	GameObject()
	{
		id_ = IdentifierManager::GetInstance().GetNewIdentifier();
	}

	inline Mesh *mesh() { return &mesh_; };

	virtual void OnUpdate() = 0;

	inline int id() { return id_; };
    inline RenderType render_type() { return render_type_; };
	inline std::string name() { return name_; };
    inline glm::vec2 position() { return position_; };
private:
	int id_;

protected:
    RenderType render_type_;
	std::string name_;
	Mesh mesh_;
    glm::vec2 position_;
};
