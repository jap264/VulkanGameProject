#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"

#include "enemy_cube.h"
#include "player.h"

static Cube *cube = { 0 };

void cube_init()
{
	cube = (Cube *)gfc_allocate_array(sizeof(Cube), 1);

	cube->ent = cube_new();
	cube->ent->position = vector3d(0, 0, 8);
	cube->ent->velocity = vector3d(0, 0, 0);
	cube->ent->rotation = vector3d(0, 0, 0);
}

Entity *cube_new()
{
	return gf3d_entity_new();
}

void cube_free(Cube *cube)
{
	if (!cube) return;

	gf3d_entity_free(cube->ent);
	memset(cube, 0, sizeof(Cube));
}

void cube_think(Entity *self)
{
	if (!self) return;
	//follow(self, player);

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position);

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.002,
		vector3d(1, 0, 0));
}

Entity *get_cube_entity()
{
	return cube->ent;
}

Cube *get_cube()
{
	return cube;
}