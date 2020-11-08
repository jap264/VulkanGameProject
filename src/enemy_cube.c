#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_cube.h"
#include "player.h"
#include "gf3d_entity.h"

static Cube *cube = { 0 };
static float rotation = 0;

void cube_init()
{
	Cube *cube;
	Entity *cubeEnt = NULL;
	cube = (Cube *)gfc_allocate_array(sizeof(Cube), 1);

	cube->ent = cube_new();
	gfc_word_cpy(cube->ent->name, "cube");
	cube->ent->position = vector3d(0, 0, 12);
	gfc_matrix_make_translation(cube->ent->modelMatrix, cube->ent->position);
	cube->ent->velocity = vector3d(0, 0, 0);
	cube->ent->rotation = vector3d(0, 0, 0);
	cube->ent->radius = 2;

	cube->ent->model = gf3d_model_load("cube");
	cube->ent->think = cube_think;
	cube->ent->die = cube_free;
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
	follow(self, get_player_entity(), 0.03);

	rotation -= 0.0015;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(0, 0, 1));
}

Entity *get_cube_entity()
{
	return cube->ent;
}

Cube *get_cube()
{
	return cube;
}