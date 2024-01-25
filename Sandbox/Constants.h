#pragma once

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}

// Levels

// Tile Groups

#define GROUP_NAME_COLLISION			"Collision"
#define GROUP_NAME_ENVIRONMENT			"Environment"

// Parallax

#define PARALLAX_NAME_0					"BGFront"
#define PARALLAX_NAME_1					"BGBack"
#define PARALLAX_NAME_2					"CloudsFront"
#define PARALLAX_NAME_3					"CloudsBack"

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
#define KNIGHT_ANIM_CROUCHALL						"CrouchAll"
#define KNIGHT_ANIM_CROUCHALL						3
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
#define KNIGHT_ANIM_JUMPFALLINBETWEEN				2
#define KNIGHT_ANIM_RUN								"Run"
#define KNIGHT_ANIM_RUN_FRAMES						10
#define KNIGHT_ANIM_TURN_ARROUND					"TurnArround"
#define KNIGHT_ANIM_TURN_ARROUND_FRAMES				3

// Skeleton

#define SKELETON_ANIM_IDLE				"Idle"
#define SKELETONO_ANIM_IDLE_FRAMES		4