#pragma once

#include "../utils/IdentifierManager.h"
#include "../renderer/Mesh.h"

class GameObject
{
public:
	GameObject()
	{
		id_ = IdentifierManager::GetInstance().GetNewIdentifier();
		mesh_ = nullptr;
	}

	inline Mesh *mesh() { return mesh_; };

	virtual void OnUpdate() = 0;

	inline int id() { return id_; };
	inline std::string name() { return name_; };
private:
	int id_;

protected:
	std::string name_;
	Mesh *mesh_;
};
