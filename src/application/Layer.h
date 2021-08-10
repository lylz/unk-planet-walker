#pragma once

#include "ApplicationSettings.h"

class Layer
{
public:
    Layer(ApplicationSettings *application_settings)
        : application_settings_(application_settings)
    {};

	virtual void Init() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;

	inline bool visible() { return visible_; };
	inline void SetVisible(bool visible) { visible_ = visible; };

protected:
	bool visible_;

    ApplicationSettings *application_settings_;
};
