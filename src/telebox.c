#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "telebox.h"
#include "player.h"
#include "gf3d_entity.h"

static Telebox *telebox = { 0 };
static float rotation = 0;
enum type{ _player, _powerup, _enemy, _spikebox, _hidebox, _telebox};

void telebox_init(Vector3D *position)
{
	Telebox *telebox;
	Entity *teleboxEnt = NULL;
	telebox = (Telebox *)gfc_allocate_array(sizeof(Telebox), 1);

	telebox->ent = telebox_new();
	gfc_word_cpy(telebox->ent->name, "telebox");
	telebox->ent->type = _telebox;
	telebox->ent->position = *position;
	gfc_matrix_make_translation(telebox->ent->modelMatrix, telebox->ent->position);
	telebox->ent->velocity = vector3d(0, 0, 0);
	telebox->ent->rotation = vector3d(0, 0, 0);
	telebox->ent->radius = 10;

	telebox->ent->model = gf3d_model_load("telebox");
	telebox->ent->model->frameCount = 2;
	telebox->ent->think = telebox_think;
	telebox->ent->die = telebox_free;
}

Entity *telebox_new()
{
	return gf3d_entity_new();
}

void telebox_free(Telebox *telebox)
{
	if (!telebox) return;

	gf3d_entity_free(telebox->ent);
	memset(telebox, 0, sizeof(Telebox));
}

void telebox_think(Entity *self)
{
	if (!self) return;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.0004,
		vector3d(0, 0, 1));
}

Entity *get_telebox_entity()
{
	return telebox->ent;
}

Telebox *get_telebox()
{
	return telebox;
}