#include "Layer.h"
#include "GraphicsConstants.h"
#include "Camera.h"
#include "Tileset.h"
#include <iostream>
#include "GameState.h"

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
	m_tile_brush.outline_opacity = 0.0f;

	SETCOLOR(m_debug_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_debug_brush.fill_opacity = 0.0f;
	m_debug_brush.outline_opacity = 1.0f;

	GameObject::init();
}

void Layer::draw()
{
	float zoom = Camera::inst()->getZoom();
	float focal_point_x = Camera::inst()->getFocalPointX();
	float focal_point_y = Camera::inst()->getFocalPointY();

	bool is_debug_mode_on = GameState::inst()->m_is_debug_mode;

	float x_pixels;
	float y_pixels;
	float width_pixels = TILE_WIDTH * zoom;
	float height_pixels = TILE_HEIGHT * zoom;
	float half_width_pixels = width_pixels / 2.0f;
	float half_height_pixels = height_pixels / 2.0f;

	int map_x_index = 0;
	int map_y_index = m_height - 1;

	int map_value;

	for (int y = m_height - 1; y >= 0; y--)
	{
		for (int x = 0; x < m_width; x++)
		{
			// Check if the tile is valid else skip
			map_value = m_map[y * m_width + x];
			if (map_value == -1) continue;
			
			// Culling if tile is inside window else skip
			x_pixels = (x * TILE_WIDTH - focal_point_x);// + TILE_WIDTH * zoom;
			
			//if (x_pixels > WINDOW_WIDTH || x_pixels + width_pixels < 0) continue;

			y_pixels = (y * TILE_HEIGHT - focal_point_y); //+ TILE_HEIGHT * zoom;

			//if (y_pixels > WINDOW_HEIGHT || y_pixels + height_pixels < 0) continue;
			// 
			// Draw
			m_tile_brush.texture = m_tileset->m_tileset_path + m_tileset->m_index_to_texture[map_value] + ".png";
			graphics::drawRect(graphics::windowToCanvasX(x_pixels + half_width_pixels, false),
							   graphics::windowToCanvasY(y_pixels + half_height_pixels, false),
							   graphics::windowToCanvasX(width_pixels, false),
							   graphics::windowToCanvasY(height_pixels, false),
							   m_tile_brush);

			if (is_debug_mode_on)
			{
				graphics::drawRect(graphics::windowToCanvasX(x_pixels + half_width_pixels, false),
					graphics::windowToCanvasY(y_pixels + half_height_pixels, false),
					graphics::windowToCanvasX(width_pixels, false),
					graphics::windowToCanvasY(height_pixels, false),
					m_debug_brush);
			}
		}

		//std::cout << std::endl;
	}

	GameObject::draw();
}
