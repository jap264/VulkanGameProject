#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_donut.h"
#include "player.h"
#include "gf3d_entity.h"

static Donut *donut = { 0 };
static float rotation = 0;

void donut_init()
{
	Donut *donut;
	Entity *donutEnt = NULL;
	donut = (Donut *)gfc_allocate_array(sizeof(Donut), 1);

	donut->ent = donut_new();
	donut->ent->position = vector3d(0, 0, 8);
	gfc_matrix_make_translation(donut->ent->modelMatrix, donut->ent->position);
	donut->ent->velocity = vector3d(0, 0, 0);
	donut->ent->rotation = vector3d(0, 0, 0);

	donut->ent->model = gf3d_model_load("donut");
	donut->ent->think = donut_think;
	donut->ent->die = donut_free;
}

Entity *donut_new()
{
	return gf3d_entity_new();
}

void donut_free(Donut *donut)
{
	if (!donut) return;

	gf3d_entity_free(donut->ent);
	memset(donut, 0, sizeof(Donut));
}

void donut_think(Entity *self)
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

Entity *get_donut_entity()
{
	return donut->ent;
}

Donut *get_donut()
{
	return donut;
}