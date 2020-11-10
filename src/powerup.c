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
enum pType{ health, speed, jump, invincibility, nuke};

static int integer(float f);

void powerup_init()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	gfc_word_cpy(powerup->ent->name, "powerup");
	powerup->ent->type = _powerup;
	powerup->ent->radius = 10;

	powerup_spawn(powerup);
	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

void powerup_spawn(Powerup *powerup)
{
	int rand = randNum(); //picks a rand num 0-9, 5-9 has no powerup
	
	if (rand > 4) return;

	else if (rand == 0)
	{
		powerup->ent->model = gf3d_model_load("powerup_health");
		gfc_word_cpy(powerup->ent->name, "powerup_health");
		powerup->ent->pType = health;
		powerup->ent->position = vector3d(-10, -6, 10); //top
	}

	else if (rand == 1)
	{
		powerup->ent->model = gf3d_model_load("powerup_speed");
		gfc_word_cpy(powerup->ent->name, "powerup_speed");
		powerup->ent->pType = speed;
		powerup->ent->position = vector3d(-12, -8, 10); //left
	}

	else if (rand == 2)
	{
		powerup->ent->model = gf3d_model_load("powerup_jump");
		gfc_word_cpy(powerup->ent->name, "powerup_jump");
		powerup->ent->pType = jump;
		powerup->ent->position = vector3d(-11, -10, 10); //bottom left
	}

	else if (rand == 3)
	{
		powerup->ent->model = gf3d_model_load("powerup_invincibility");
		gfc_word_cpy(powerup->ent->name, "powerup_invincibility");
		powerup->ent->pType = invincibility;
		powerup->ent->position = vector3d(-9, -10, 10); //bottom right
	}

	else
	{
		powerup->ent->model = gf3d_model_load("powerup_nuke");
		gfc_word_cpy(powerup->ent->name, "powerup_nuke");
		powerup->ent->pType = nuke;
		powerup->ent->position = vector3d(-8, -8, 10); //right
	}

	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);
}

void powerup_health()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	powerup->ent->type = _powerup;
	powerup->ent->radius = 3;
	powerup->ent->model = gf3d_model_load("powerup_health");
	gfc_word_cpy(powerup->ent->name, "powerup_health");
	powerup->ent->pType = health;
	powerup->ent->position = vector3d(-10, -6, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);

	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

void powerup_speed()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	powerup->ent->type = _powerup;
	powerup->ent->radius = 3;
	powerup->ent->model = gf3d_model_load("powerup_speed");
	gfc_word_cpy(powerup->ent->name, "powerup_speed");
	powerup->ent->pType = speed;
	powerup->ent->position = vector3d(-12, -8, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);

	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

void powerup_jump()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	powerup->ent->type = _powerup;
	powerup->ent->radius = 3;
	powerup->ent->model = gf3d_model_load("powerup_jump");
	gfc_word_cpy(powerup->ent->name, "powerup_jump");
	powerup->ent->pType = jump;
	powerup->ent->position = vector3d(-11, -10, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);

	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

void powerup_invincibility()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	powerup->ent->type = _powerup;
	powerup->ent->radius = 3;
	powerup->ent->model = gf3d_model_load("powerup_invincibility");
	gfc_word_cpy(powerup->ent->name, "powerup_invincibility");
	powerup->ent->pType = invincibility;
	powerup->ent->position = vector3d(-9, -10, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);

	powerup->ent->think = powerup_think;
	powerup->ent->die = powerup_free;
}

void powerup_nuke()
{
	Powerup *powerup;
	Entity *powerupEnt = NULL;
	powerup = (Powerup *)gfc_allocate_array(sizeof(Powerup), 1);

	powerup->ent = powerup_new();
	powerup->ent->type = _powerup;
	powerup->ent->radius = 3;
	powerup->ent->model = gf3d_model_load("powerup_nuke");
	gfc_word_cpy(powerup->ent->name, "powerup_nuke");
	powerup->ent->pType = nuke;
	powerup->ent->position = vector3d(-8, -8, 10);
	gfc_matrix_make_translation(powerup->ent->modelMatrix, powerup->ent->position);

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

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.0015,
		vector3d(0, 0, 1));
}

Entity *get_powerup_entity()
{
	return powerup->ent;
}

Powerup *get_powerup()
{
	return powerup;
}

int integer(float f)
{
	int result = f;
	return result;
}

static int randNum()
{
	return integer(gfc_crandom() * 5 + 5);
}