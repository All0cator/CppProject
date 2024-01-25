#pragma once

#include "GameObject.h"

class ParallaxBackground : public GameObject
{
private:

public:
	ParallaxBackground(float horizontalSpeed, float verticalSpeed = 1.0f);
	virtual ~ParallaxBackground();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
};