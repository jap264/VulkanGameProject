#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"

#include "enemy_sphere.h"
#include "player.h"

static Sphere *sphere = { 0 };
int sphereJump = 0;

void sphere_init()
{
	sphere = (Sphere *)gfc_allocate_array(sizeof(Sphere), 1);

	sphere->ent = sphere_new();
	sphere->ent->position = vector3d(0, 0, 8);
	sphere->ent->velocity = vector3d(0, 0, 0);
	sphere->ent->rotation = vector3d(0, 0, 0);
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
	//follow(self, player);

	if (sphereJump == 0 && self->position.z <= 10)
	{
		self->position.z += 0.005;
	}

	if (self->position.z > 10)
	{
		sphereJump = 1;
		//slog("%i", sphereJump);
	}

	if (sphereJump == 1 && self->position.z > -5)
	{
		self->position.z -= 0.005;
	}

	if (self->position.z < -5) sphereJump = 0;

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position);
}

Entity *get_sphere_entity()
{
	return sphere->ent;
}

Sphere *get_sphere()
{
	return sphere;
}