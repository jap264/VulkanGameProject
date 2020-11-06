#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_cylinder.h"
#include "player.h"
#include "gf3d_entity.h"

static Cylinder *cylinder = { 0 };
static float rotation = 0;

void cylinder_init()
{
	Cylinder *cylinder;
	Entity *cylinderEnt = NULL;

	cylinder = (Cylinder *)gfc_allocate_array(sizeof(Cylinder), 1);

	cylinder->ent = cylinder_new();
	cylinder->ent->position = vector3d(0, 0, 8);
	gfc_matrix_make_translation(cylinder->ent->modelMatrix, cylinder->ent->position);
	cylinder->ent->velocity = vector3d(0, 0, 0);
	cylinder->ent->rotation = vector3d(0, 0, 0);

	cylinder->ent->model = gf3d_model_load("cylinder");
	cylinder->ent->think = cylinder_think;
	cylinder->ent->die = cylinder_free;
}

Entity *cylinder_new()
{
	return gf3d_entity_new();
}

void cylinder_free(Cylinder *cylinder)
{
	if (!cylinder) return;

	gf3d_entity_free(cylinder->ent);
	memset(cylinder, 0, sizeof(Cylinder));
}

void cylinder_think(Entity *self)
{
	if (!self) return;
	follow(self, get_player_entity(), 0.04);

	rotation -= 0.005;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(0, 0, 1));
}

Entity *get_cylinder_entity()
{
	return cylinder->ent;
}

Cylinder *get_cylinder()
{
	return cylinder;
}