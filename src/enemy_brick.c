#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_brick.h"
#include "player.h"
#include "gf3d_entity.h"

static Brick *brick = { 0 };
static float rotation = 0;

void brick_init()
{
	Brick *brick;
	Entity *brickEnt = NULL;
	brick = (Brick *)gfc_allocate_array(sizeof(Brick), 1);

	brick->ent = brick_new();
	gfc_word_cpy(brick->ent->name, "brick");
	brick->ent->position = vector3d(0, 0, 8);
	gfc_matrix_make_translation(brick->ent->modelMatrix, brick->ent->position);
	brick->ent->velocity = vector3d(0, 0, 0);
	brick->ent->rotation = vector3d(0, 0, 0);
	brick->ent->radius = 2;

	brick->ent->model = gf3d_model_load("brick");
	brick->ent->think = brick_think;
	brick->ent->die = brick_free;
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
	follow(self, get_player_entity(), 0.02);

	rotation -= 0.001;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(1, 1, 1));
}

Entity *get_brick_entity()
{
	return brick->ent;
}

Brick *get_brick()
{
	return brick;
}