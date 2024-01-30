#include "Layer.h"
#include "GraphicsConstants.h"
#include "Camera.h"
#include "Tileset.h"
#include <iostream>

Layer::Layer(GameState* gs, const std::string& name, 
			 Tileset * tileset, 
			 int width, int height, 
			 const std::vector<int>& map)
	: GameObject(gs, name)
{
	m_tileset = tileset;
	if (m_tileset == nullptr)
	{
		std::cout << "Error: Tileset is nullptr" << std::endl;
	}

	this->m_width = width;
	this->m_height = height;
	this->m_map = map;
}

Layer::~Layer()
{}

void Layer::update(float dt)
{
	GameObject::update(dt);
}

void Layer::init()
{
	SETCOLOR(m_tile_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_tile_brush.fill_opacity = 1.0f;

	GameObject::init();
}

void Layer::draw()
{
	float zoom = Camera::inst()->getZoom();
	float focal_point_x = Camera::inst()->getFocalPointX();
	float focal_point_y = Camera::inst()->getFocalPointY();

	float x_pixels;
	float y_pixels;
	float width_pixels;
	float height_pixels;

	int map_x_index = 0;
	int map_y_index = 0;

	int map_value;

	for (float y = 0.0f; y < m_height * TILE_HEIGHT * zoom; y += TILE_HEIGHT * zoom, ++map_y_index)
	{
		for (float x = 0.0f; x < m_width * TILE_HEIGHT * zoom; x += TILE_WIDTH * zoom, ++map_x_index)
		{
			// Check if the tile is valid else skip
			map_value = m_map[map_y_index * m_width + map_x_index];
			if (map_value == -1) continue;
			
			// Culling if tile is inside window else skip
			x_pixels = (x - focal_point_x) + TILE_WIDTH * zoom;
			width_pixels = TILE_WIDTH * zoom;
			
			if (x_pixels > WINDOW_WIDTH || x_pixels + width_pixels < 0) continue;

			y_pixels = (y - focal_point_y) + TILE_HEIGHT * zoom;
			height_pixels = TILE_HEIGHT * zoom;

			if (y_pixels > WINDOW_HEIGHT || y_pixels + height_pixels < 0) continue;

			// Draw
			m_tile_brush.texture = m_tileset->m_tileset_path + m_tileset->m_index_to_texture[map_value] + ".png";
			graphics::drawRect(graphics::windowToCanvasX(x_pixels),
							   graphics::windowToCanvasY(y_pixels),
							   graphics::windowToCanvasX(width_pixels),
							   graphics::windowToCanvasY(height_pixels),
							   m_tile_brush);
		}
	}

	GameObject::draw();
}
