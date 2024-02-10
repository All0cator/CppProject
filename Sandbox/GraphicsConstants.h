#pragma once

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}

#define LEVEL_MAP_WIDTH 50
#define LEVEL_MAP_HEIGHT 20
#define LEVELS_COUNT 7

// In Pixels
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 312

#define LEVEL_OFFSET_X LEVEL_MAP_WIDTH * TILE_WIDTH

// In Canvas Units
#define CANVAS_WIDTH 400.0f
#define CANVAS_HEIGHT 312.0f

// Not graphics constants :D

#define TILE_SPIKE 0
#define TILE_SOLID_TILE 1 

#define SPIKE_DMG 30.0f