#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gfc_vector.h"

#include "enemy_cylinder.h"
#include "player.h"

static Cylinder *cylinder = { 0 };

void cylinder_init()
{
	cylinder = (Cylinder *)gfc_allocate_array(sizeof(Cylinder), 1);

	cylinder->ent = cylinder_new();
	cylinder->ent->position = vector3d(0, 0, 8);
	cylinder->ent->velocity = vector3d(0, 0, 0);
	cylinder->ent->rotation = vector3d(0, 0, 0);
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
}

Entity *get_cylinder_entity()
{
	return cylinder->ent;
}

Cylinder *get_cylinder()
{
	return cylinder;
}

