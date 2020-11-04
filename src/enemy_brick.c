#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"

#include "enemy_brick.h"
#include "player.h"

static Brick *brick = { 0 };

void brick_init()
{
	brick = (Brick *)gfc_allocate_array(sizeof(Brick), 1);

	brick->ent = brick_new();
	brick->ent->position = vector3d(0, 0, 8);
	brick->ent->velocity = vector3d(0, 0, 0);
	brick->ent->rotation = vector3d(0, 0, 0);
}

Entity *brick_new()
{
	return gf3d_entity_new();
}

void brick_free(Brick *brick)
{
	if (!brick) return;

	gf3d_entity_free(brick->ent);
	memset(brick, 0, sizeof(Brick));
}

void brick_think(Entity *self)
{
	if (!self) return;
}

Entity *get_brick_entity()
{
	return brick->ent;
}

Brick *get_brick()
{
	return brick;
}