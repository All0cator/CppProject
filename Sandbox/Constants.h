#pragma once

// Levels

// Tile Groups

#define GROUP_NAME_COLLISION			"Collision"
#define GROUP_NAME_COLLISION_NUM		2
#define GROUP_NAME_ENVIRONMENT			"Environment"
#define GROUP_NAME_ENVIRONMENT_NUM		9

// Tile sets
#define TILESET_FOREST					"forest"
#define TILESET_FOREST_TEXTURES_MAX		57
#define TILESET_TREES					"trees"
#define TILESET_TREES_TEXTURES_MAX		126
#define TILESET_COLLISION_TILE			"collision_tile"
#define TILESET_COLLISION_TILE_MAX		1

#define TILESET_COUNT					3
// Parallax

#define PARALLAX_WIDTH 512
#define PARALLAX_HEIGHT 320

#define PARALLAX_NAME_0					"CloudsBack"
#define PARALLAX_NAME_0_SPEED_X			0.25f
#define PARALLAX_NAME_0_SPEED_Y			1.0f
#define PARALLAX_NAME_1					"CloudsFront"
#define PARALLAX_NAME_1_SPEED_X			0.5f
#define PARALLAX_NAME_1_SPEED_Y			1.0f
#define PARALLAX_NAME_2					"BGBack"
#define PARALLAX_NAME_2_SPEED_X			0.75f	
#define PARALLAX_NAME_2_SPEED_Y			1.0f
#define PARALLAX_NAME_3					"BGFront"
#define PARALLAX_NAME_3_SPEED_X			0.85f
#define PARALLAX_NAME_3_SPEED_Y			1.0f

// Layers

#define LAYERS_COLLISION_SOLIDTILES		"SolidTiles"
#define LAYERS_COLLISION_SPIKES			"Spikes"

#define LAYERS_ENVIRONMENT_SPIKES		"Spikes"
#define LAYERS_ENVIRONMENT_BRIDGES		"Bridges"
#define LAYERS_ENVIRONMENT_FENCES		"Fences"
#define LAYERS_ENVIRONMENT_GRASS		"Grass"
#define LAYERS_ENVIRONMENT_BUSHES		"Bushes"
#define LAYERS_ENVIRONMENT_BIGTREES		"BigTrees"
#define LAYERS_ENVIRONMENT_SMALLTREES	"SmallTrees"
#define LAYERS_ENVIRONMENT_ROCKSFORE	"RocksForeground"
#define LAYERS_ENVIRONMENT_ROCKSBACK	"RocksBackground"


// Knight

#define KNIGHT_ANIM_ATTACKCOMBO2HIT					"AttackCombo2hit"
#define KNIGHT_ANIM_ATTACKCOMBO2HIT_FRAMES			10
#define KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT			"AttackComboNoMovement"
#define KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT_FRAMES	10
#define KNIGHT_ANIM_CROUCHIDLE						"CrouchIdle"
#define KNIGHT_ANIM_CROUCHIDLE_FRAMES			    1
#define KNIGHT_ANIM_CROUCHATTACK					"CrouchAttack"
#define KNIGHT_ANIM_CROUCHATTACK_FRAMES				4
#define KNIGHT_ANIM_CROUCHTRANSITION				"CrouchTransition"
#define KNIGHT_ANIM_CROUCHTRANSITION_FRAMES			1
#define KNIGHT_ANIM_CROUCHWALK						"CrouchWalk"
#define KNIGHT_ANIM_CROUCHWALK_FRAMES				8
#define KNIGHT_ANIM_DASH							"Dash"
#define KNIGHT_ANIM_DASH_FRAMES						2
#define KNIGHT_ANIM_DEATH							"Death"
#define KNIGHT_ANIM_DEATH_FRAMES					10
#define KNIGHT_ANIM_DEATHNOMOVEMENT					"DeathNoMovement"
#define KNIGHT_ANIM_DEATHNOMOVEMENT_FRAMES			10
#define KNIGHT_ANIM_FALL							"Fall"
#define KNIGHT_ANIM_FALL_FRAMES						3
#define KNIGHT_ANIM_HIT								"Hit"
#define KNIGHT_ANIM_HIT_FRAMES						1
#define KNIGHT_ANIM_IDLE							"Idle"
#define KNIGHT_ANIM_IDLE_FRAMES						10
#define KNIGHT_ANIM_JUMP							"Jump"
#define KNIGHT_ANIM_JUMP_FRAMES						3
#define KNIGHT_ANIM_JUMPFALLINBETWEEN				"JumpFallInBetween"
#define KNIGHT_ANIM_JUMPFALLINBETWEEN_FRAMES		2
#define KNIGHT_ANIM_RUN								"Run"
#define KNIGHT_ANIM_RUN_FRAMES						10
#define KNIGHT_ANIM_TURN_ARROUND					"TurnArround"
#define KNIGHT_ANIM_TURN_ARROUND_FRAMES				3

// Skeleton

#define SKELETON_ANIM_ATTACK			"Attack"
#define SKELETON_ANIM_ATTACK_FRAMES		13
#define SKELETON_ANIM_DEATH				"Death"
#define SKELETON_ANIM_DEATH_FRAMES		13
#define SKELETON_ANIM_HIT				"Hit"
#define SKELETON_ANIM_HIT_FRAMES		3
#define SKELETON_ANIM_IDLE				"Idle"
#define SKELETON_ANIM_IDLE_FRAMES		4
#define SKELETON_ANIM_WALK				"Walk"
#define SKELETON_ANIM_WALK_FRAMES		12