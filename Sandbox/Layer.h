#pragma once
#include "GameObject.h"
#include <unordered_map>

class Layer : public GameObject
{
private:
	std::string name;
	// Maps index of tile to the graphic texture
	std::unordered_map<int, std::string> indexToTexture;

	// Number of tiles horizontally and vertically
	int width;
	int height;
	// The array of indices
	int* map;

public:
	Layer();
	virtual ~Layer();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
};