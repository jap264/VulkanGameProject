#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "explosion.h"
#include "player.h"
#include "gf3d_entity.h"

static Explosion *explosion = { 0 };
static float rotation = 0;
enum type{ _player, _powerup, _enemy, _spikebox, _hidebox, _telebox, _dog, _explosion };

void explosion_init(Vector3D position)
{
	Explosion *explosion;
	Entity *explosionEnt = NULL;
	explosion = (Explosion *)gfc_allocate_array(sizeof(Explosion), 1);

	explosion->ent = explosion_new();
	gfc_word_cpy(explosion->ent->name, "explosion");
	explosion->ent->type = _explosion;
	explosion->ent->position = position;
	gfc_matrix_make_translation(explosion->ent->modelMatrix, explosion->ent->position);
	explosion->ent->velocity = vector3d(0, 0, 0);
	explosion->ent->rotation = vector3d(0, 0, 0);
	explosion->ent->radius = 0;

	explosion->ent->model = gf3d_model_load_animated("explosion", 1, 30);
	explosion->ent->model->frameCount = 29;
	explosion->ent->isAnimated = 1;
	explosion->ent->maxFrames = explosion->ent->model->frameCount;
	explosion->ent->timeToLive = 1700;
	explosion->ent->think = explosion_think;
	explosion->ent->die = explosion_free;
}

Entity *explosion_new()
{
	return gf3d_entity_new();
}

void explosion_free(Explosion *explosion)
{
	if (!explosion) return;

	gf3d_entity_free(explosion->ent);
	memset(explosion, 0, sizeof(Explosion));
}

void explosion_think(Entity *self)
{
	if (!self) return;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.0005,
		vector3d(0, 0, 1));

	if (self->timeToLive > 0) self->timeToLive--;
	if (self->timeToLive == 0) gf3d_entity_free(self);
}

Entity *get_explosion_entity()
{
	return explosion->ent;
}

Explosion *get_explosion()
{
	return explosion;
}