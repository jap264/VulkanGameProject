#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "player.h"

static Player *player = { 0 };

void player_move(Entity *self);

int delayD = 0;
int delaySS = 0;
int delayJump = 0;
int delaySprint = 10000;
double beforeD;
double beforeSS;
int dash = 0;
int sidestep1 = 0;
int sidestep2 = 0;
int jump = 0;
int jumping = 0;
int sprintCount = 0;
int sprintCheck = 0;

void player_init()
{
	player = (Player *)gfc_allocate_array(sizeof(Player), 1);

	player->ent = player_new();
	player->ent->position = vector3d(0, 0, 8);
	player->ent->velocity = vector3d(0, 0, 0);
	player->ent->rotation = vector3d(0, 0, 0);
	player->ent->model = gf3d_model_load("dino");
	player->ent->think = player_think;
}

Entity *player_new()
{
	return gf3d_entity_new();
}

void player_free(Player *player)
{
	if (!player) return;

	gf3d_entity_free(player->ent);
	memset(player, 0, sizeof(Player));
}

void player_think(Entity *self)
{
	const Uint8 *keys;
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);

	//-----------------------------------
	//DELAYS
	//-----------------------------------

	if (delayD > 0) //DASH DELAY
	{
		delayD--;
		//slog("%i", delayD);
	}

	if (delaySS > 0) //SIDESTEP DELAY
	{
		delaySS--;
		//slog("%i", delaySS);
	}

	if (delayJump > 0) //JUMP DELAY
	{
		delayJump--;
		//slog("%i", delaySS);
	}

	//-----------------------------------
	//AREA CHECKING
	//-----------------------------------

	//FLYZONE
	int jumpheight = 43;
	if (self->position.x > -40 && self->position.x < 22 && self->position.y > -40 && self->position.y < 40) jumpheight = 80;

	//FOREST
	int jumpBool = 1;
	if (self->position.x > -140 && self->position.x < 122 && self->position.y > -130 && self->position.y < 135) jumpBool = 0;
	if (self->position.x > -40 && self->position.x < 22 && self->position.y > -40 && self->position.y < 40) jumpBool = 1;

	//DESERT
	float sprintDistance = 0.12;
	if (self->position.x > -235 && self->position.x < 235 && self->position.y > -225 && self->position.y < 225) sprintDistance = 0.05;
	if (self->position.x > -140 && self->position.x < 122 && self->position.y > -130 && self->position.y < 135) sprintDistance = 0.12;

	//RIVERS

	//Top River
	if (self->position.x > -295 && self->position.x < 295 && self->position.y > 220 && self->position.y < 285) self->position.y -= 0.04;

	//Bottom River
	if (self->position.x > -295 && self->position.x < 295 && self->position.y > -295 && self->position.y < -230) self->position.y += 0.04;

	//Left River
	if (self->position.x > -295 && self->position.x < -235 && self->position.y > -295 && self->position.y < 285) self->position.x += 0.04;
	
	//Right River
	if (self->position.x > 240 && self->position.x < 295 && self->position.y > -295 && self->position.y < 285) self->position.x -= 0.04;

	//QUICKSAND
	float quicksand = 0;
	if (self->position.x > -295 && self->position.x < 295 && self->position.y > -300 && self->position.y < 285) quicksand = 0;
	else
	{
		quicksand = 1;
		jumpBool = 0;
	}

	//-----------------------------------
	//SPRINT
	//-----------------------------------
	
	if (!keys[SDL_SCANCODE_LSHIFT]) sprintCount -= 0.1;

	if (sprintCount >= 8000)
	{
		sprintCheck = 1;
	}

	if (sprintCheck == 1)
	{
		delaySprint--;
	}

	if (delaySprint <= 0)
	{
		sprintCheck = 0;
		sprintCount = 0;
	}

	if (sprintCheck == 0)
	{
		delaySprint = 10000;
	}

	//-----------------------------------
	//BASIC MOVEMENT
	//-----------------------------------

	if (keys[SDL_SCANCODE_W] && self->position.y < 296)
	{
		if (quicksand == 1)
		{
			self->position.y += 0.001;
		}

		else if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.y += sprintDistance;
			sprintCount++;
			slog("sprint forward %f", sprintDistance);
		}
		
		else
		{
			self->position.y += 0.07;
			slog("forward");
		}
	}

	if (keys[SDL_SCANCODE_A] && self->position.x > -300)
	{
		if (quicksand == 1)
		{
			self->position.x -= 0.001;
		}

		else if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.x -= sprintDistance - 0.02;
			sprintCount++;
			slog("sprint left %f", sprintDistance - 0.02);
		}
		
		else
		{
			self->position.x -= 0.05;
			slog("left");
		}
	}

	if (keys[SDL_SCANCODE_S] && self->position.y > -305)
	{
		if (quicksand == 1)
		{
			self->position.y -= 0.001;
		}

		else if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.y -= sprintDistance;
			sprintCount++;
			slog("sprint backward %f", sprintDistance);
		}
		
		else
		{
			self->position.y -= 0.07;
			slog("backward");
		}
	}

	if (keys[SDL_SCANCODE_D] && self->position.x < 300)
	{
		if (quicksand == 1)
		{
			self->position.x += 0.001;
		}

		else if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.x += sprintDistance - 0.02;
			sprintCount++;
			slog("sprint right %f", sprintDistance - 0.02);
		}
		
		else
		{
			self->position.x += 0.05;
			slog("right");
		}
	}

	//-----------------------------------
	//JUMP
	//-----------------------------------

	if (keys[SDL_SCANCODE_SPACE] && self->position.z == 8 && jump == 0 && delayJump == 0 && jumpBool == 1)
	{
		//self->position.z += 15;
		jump = 2;
		slog("jumping");
		slog("x: %f, y: %f", self->position.x, self->position.y);
	}

	if (jump == 2 && self->position.z < jumpheight)
	{
		self->position.z += 0.1;
	}

	if (self->position.z >= jumpheight)
	{
		jump = 1;
		delayJump = 3000;
	}

	if (self->position.z > 8 && jump == 1)
	{
		if (keys[SDL_SCANCODE_SPACE])
		{
			self->position.z -= 0.008;
		}
		
		else
		{
			self->position.z -= 0.05;
		}
	}

	if (self->position.z <= 8)
	{
		self->position.z = 8;
		jump = 0;
	}

	//-----------------------------------
	//DASH
	//-----------------------------------

	if (keys[SDL_SCANCODE_F] && delayD == 0)
	{
		delayD = 3000;
		dash = 1;
		beforeD = self->position.y;
		//self->position.y += 30;
		slog("dashed");
	}

	if (dash == 1 && ((self->position.y - beforeD) < 80))
	{
		self->position.y += 0.25;
	}

	if (self->position.y - beforeD >= 80)
	{
		dash = 0;
	}

	//-----------------------------------
	//SIDESTEP
	//-----------------------------------

	if (keys[SDL_SCANCODE_Q] && delaySS == 0)
	{
		delaySS = 2000;
		sidestep1 = 1;
		beforeSS = self->position.x;
		//self->position.x -= 15;
		slog("sidestep1");
	}

	if (sidestep1 == 1 && ((self->position.x - beforeSS) > -60))
	{
		self->position.x -= 0.25;
	}

	if (self->position.x - beforeSS <= -60)
	{
		sidestep1 = 0;
	}

	if (keys[SDL_SCANCODE_E] && delaySS == 0)
	{
		delaySS = 2000;
		sidestep2 = 1;
		beforeSS = self->position.x;
		//self->position.x += 15;
		slog("sidestep2");
	}

	if (sidestep2 == 1 && ((self->position.x - beforeSS) < 60))
	{
		self->position.x += 0.25;
	}

	if (self->position.x - beforeSS >= 60)
	{
		sidestep2 = 0;
	}

	//-------------------------------

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
		);
}

Entity *get_player_entity()
{
	return player->ent;
}

Player *get_player()
{
	return player;
}