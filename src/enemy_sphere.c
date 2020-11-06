#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_sphere.h"
#include "player.h"
#include "gf3d_entity.h"

static Sphere *sphere = { 0 };
static float rotation = 0;

void sphere_init()
{
	Sphere *sphere;
	Entity *sphereEnt = NULL;

	sphere = (Sphere *)gfc_allocate_array(sizeof(Sphere), 1);

	sphere->ent = sphere_new();
	sphere->ent->position = vector3d(0, 0, 8);
	gfc_matrix_make_translation(sphere->ent->modelMatrix, sphere->ent->position);
	sphere->ent->velocity = vector3d(0, 0, 0);
	sphere->ent->rotation = vector3d(0, 0, 0);

	sphere->ent->model = gf3d_model_load("cylinder"); //fix sphere model load
	sphere->ent->think = sphere_think;
	sphere->ent->die = sphere_free;
}

Entity *sphere_new()
{
	return gf3d_entity_new();
}

void sphere_free(Sphere *sphere)
{
	if (!sphere) return;

	gf3d_entity_free(sphere->ent);
	memset(sphere, 0, sizeof(Sphere));
}

void sphere_think(Entity *self)
{
	if (!self) return;
	follow(self, get_player_entity(), 0.025);

	//set bouncing animation
	

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
		);

	rotation -= 0.001;

	gfc_matrix_rotate( //creates spinning effect for sphere
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(1, 0, 0)
		);
	//slog("sphere position: %f", self->position.z);
}

Entity *get_sphere_entity()
{
	return sphere->ent;
}

Sphere *get_sphere()
{
	return sphere;
}