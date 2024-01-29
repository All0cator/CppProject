#include "Layer.h"
#include "GraphicsConstants.h"
#include "Camera.h"

Layer::Layer(GameState* gs, const std::string& name, 
			 const std::string& tileset_path, 
			 int width, int height, 
			 int* map)
	: GameObject(gs, name)
{
	this->m_tileset_path = tileset_path;
	this->m_width = width;
	this->m_height = height;
	this->m_map = map;
}

Layer::~Layer()
{
}

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

	for (float y = 0.0f; y < m_height; y += TILE_HEIGHT * zoom)
	{
		for (float x = 0.0f; x < m_width; x += TILE_WIDTH * zoom)
		{
			// Check if the tile has a texture else skip
			const auto& iter = m_index_to_texture.find(m_map[y * m_width + x]);
			if (iter == m_index_to_texture.end()) continue;
			
			// Culling if tile is inside window else skip
			x_pixels = (x - focal_point_x) + TILE_WIDTH * zoom;
			width_pixels = TILE_WIDTH * zoom;
			
			if (x_pixels > WINDOW_WIDTH || x_pixels + width_pixels < 0) continue;

			y_pixels = (y - focal_point_y) + TILE_HEIGHT * zoom;
			height_pixels = TILE_HEIGHT * zoom;

			if (y_pixels > WINDOW_HEIGHT || y_pixels + height_pixels < 0) continue;

			// Draw
			m_tile_brush.texture = iter->second;
			graphics::drawRect(graphics::windowToCanvasX(x_pixels),
							   graphics::windowToCanvasY(y_pixels),
							   graphics::windowToCanvasX(width_pixels),
							   graphics::windowToCanvasY(height_pixels),
							   m_tile_brush);
		}
	}

	GameObject::draw();
}
