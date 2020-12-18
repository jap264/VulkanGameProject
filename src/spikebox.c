#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "spikebox.h"
#include "player.h"
#include "gf3d_entity.h"

static Spikebox *spikebox = { 0 };
static float rotation = 0;
enum type{ _player, _powerup, _enemy, _spikebox};

void spikebox_init(Vector3D *position)
{
	Spikebox *spikebox;
	Entity *spikeboxEnt = NULL;
	spikebox = (Spikebox *)gfc_allocate_array(sizeof(Spikebox), 1);

	spikebox->ent = spikebox_new();
	gfc_word_cpy(spikebox->ent->name, "spikebox");
	spikebox->ent->type = _spikebox;
	spikebox->ent->position = *position;
	gfc_matrix_make_translation(spikebox->ent->modelMatrix, spikebox->ent->position);
	spikebox->ent->velocity = vector3d(0, 0, 0);
	spikebox->ent->rotation = vector3d(0, 0, 0);
	spikebox->ent->radius = 14;

	spikebox->ent->model = gf3d_model_load("spikebox");
	spikebox->ent->model->frameCount = 2;
	spikebox->ent->think = spikebox_think;
	spikebox->ent->die = spikebox_free;
}

Entity *spikebox_new()
{
	return gf3d_entity_new();
}

void spikebox_free(Spikebox *spikebox)
{
	if (!spikebox) return;

	gf3d_entity_free(spikebox->ent);
	memset(spikebox, 0, sizeof(Spikebox));
}

void spikebox_think(Entity *self)
{
	if (!self) return;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.0015,
		vector3d(0, 0, 1));
}

Entity *get_spikebox_entity()
{
	return spikebox->ent;
}

Spikebox *get_spikebox()
{
	return spikebox;
}