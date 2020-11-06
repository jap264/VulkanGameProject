#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_cone.h"
#include "player.h"
#include "gf3d_entity.h"

static Cone *cone = { 0 };
static float rotation = 0;

void cone_init()
{
	Cone *cone;
	Entity *coneEnt = NULL;
	
	cone = (Cone *)gfc_allocate_array(sizeof(Cone), 1);

	cone->ent = cone_new();
	cone->ent->position = vector3d(0, 0, 8);
	gfc_matrix_make_translation(cone->ent->modelMatrix, cone->ent->position);
	cone->ent->velocity = vector3d(0, 0, 0);
	cone->ent->rotation = vector3d(0, 0, 0);

	cone->ent->model = gf3d_model_load("cone");
	cone->ent->think = cone_think;
	cone->ent->die = cone_free;
}

Entity *cone_new()
{
	return gf3d_entity_new();
}

void cone_free(Cone *cone)
{
	if (!cone) return;

	gf3d_entity_free(cone->ent);
	memset(cone, 0, sizeof(Cone));
}

void cone_think(Entity *self)
{
	if (!self) return;
	follow(self, get_player_entity(), 0.035);
	
	//set follow code for the z direction
	if (self->position.z - 5 >  get_player_entity()->position.z)
	{
		self->position.z -= 0.03;
	}

	if (self->position.z - 5 <  get_player_entity()->position.z)
	{
		self->position.z += 0.03;
	}

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
		);

	rotation += 0.001;

	gfc_matrix_rotate( //creates spinning effect for cone
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(0, 0, 1)
		);
	//slog("cone position: %f", self->position.z);
}

Entity *get_cone_entity()
{
	return cone->ent;
}

Cone *get_cone()
{
	return cone;
}