#include <iostream>
#include <sgg/graphics.h>
#include "GameState.h"
#include "Timer.h"

void init()
{
	GameState::inst()->init();
}

void update(float dt)
{
	GameState::inst()->update(dt);
}

void draw()
{
	GameState::inst()->draw();
}

int main()
{
	
	graphics::createWindow(GameState::inst()->getWindowWidth(), GameState::inst()->getWindowHeight(), GameState::inst()->getWindowTitle());
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(GameState::inst()->getCanvasWidth(), GameState::inst()->getCanvasHeight());
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	init();

	graphics::startMessageLoop();
	
	return 0;
}