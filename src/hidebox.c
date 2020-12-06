#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "hidebox.h"
#include "player.h"
#include "gf3d_entity.h"

static Hidebox *hidebox = { 0 };
static float rotation = 0;
enum type{ _player, _powerup, _enemy, _spikebox, _hidebox, _telebox};

void hidebox_init(Vector3D *position)
{
	Hidebox *hidebox;
	Entity *hideboxEnt = NULL;
	hidebox = (Hidebox *)gfc_allocate_array(sizeof(Hidebox), 1);

	hidebox->ent = hidebox_new();
	gfc_word_cpy(hidebox->ent->name, "hidebox");
	hidebox->ent->type = _hidebox;
	hidebox->ent->position = *position;
	gfc_matrix_make_translation(hidebox->ent->modelMatrix, hidebox->ent->position);
	hidebox->ent->velocity = vector3d(0, 0, 0);
	hidebox->ent->rotation = vector3d(0, 0, 0);
	hidebox->ent->radius = 3;

	hidebox->ent->model = gf3d_model_load("hidebox");
	hidebox->ent->think = hidebox_think;
	hidebox->ent->die = hidebox_free;
}

Entity *hidebox_new()
{
	return gf3d_entity_new();
}

void hidebox_free(Hidebox *hidebox)
{
	if (!hidebox) return;

	gf3d_entity_free(hidebox->ent);
	memset(hidebox, 0, sizeof(Hidebox));
}

void hidebox_think(Entity *self)
{
	if (!self) return;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.0001,
		vector3d(0, 0, 1));
}

Entity *get_hidebox_entity()
{
	return hidebox->ent;
}

Hidebox *get_hidebox()
{
	return hidebox;
}