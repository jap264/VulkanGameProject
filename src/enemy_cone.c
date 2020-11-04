#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"

#include "enemy_cone.h"
#include "player.h"

static Cone *cone = { 0 };

void cone_init()
{
	cone = (Cone *)gfc_allocate_array(sizeof(Cone), 1);

	cone->ent = cone_new();
	cone->ent->position = vector3d(0, 0, 8);
	cone->ent->velocity = vector3d(0, 0, 0);
	cone->ent->rotation = vector3d(0, 0, 0);
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
}

Entity *get_cone_entity()
{
	return cone->ent;
}

Cone *get_cone()
{
	return cone;
}

