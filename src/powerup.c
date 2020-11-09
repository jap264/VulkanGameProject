#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "powerup.h"
#include "player.h"
#include "gf3d_entity.h"

static Powerup *powerup = { 0 };
enum type{ _player, _powerup, _enemy };

void powerup_init()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	gfc_word_cpy(powerup->ent->name, "powerup");
	powerup->ent->type = _powerup;
	powerup->ent->position = vector3d(0, 0, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);
	powerup->ent->radius = 3;

	powerup->ent->model = gf3d_model_load("powerup_health");
	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

Entity *powerup_new()
{
	return gf3d_entity_new();
}

void powerup_free(Powerup *powerup)
{
	if (!powerup) return;

	gf3d_entity_free(powerup->ent);
	memset(powerup, 0, sizeof(Powerup));
}

void powerup_think(Entity *self)
{
	if (!self) return;
}

Entity *get_powerup_entity()
{
	return powerup->ent;
}

Powerup *get_powerup()
{
	return powerup;
}