#pragma once

class Layer
{
public:
	virtual void Init() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

	inline bool visible() { return visible_; };
	inline void SetVisible(bool visible) { visible_ = visible; };

protected:
	bool visible_;
};
