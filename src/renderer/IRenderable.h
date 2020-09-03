#pragma once

class IRenderable
{
public:
	virtual void Prepare() = 0;
	virtual void Draw() = 0;
};
