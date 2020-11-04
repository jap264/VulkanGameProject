#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
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
	//SPRINT
	//-----------------------------------

	if (sprintCount >= 5000)
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

	if (keys[SDL_SCANCODE_W])
	{
		if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.y += 0.09;
			sprintCount++;
			slog("sprint forward");
		}
		
		else
		{
			self->position.y += 0.05;
			slog("forward");
		}
	}

	if (keys[SDL_SCANCODE_A])
	{
		if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.x -= 0.09;
			sprintCount++;
			slog("sprint left");
		}
		
		else
		{
			self->position.x -= 0.05;
			slog("left");
		}
	}

	if (keys[SDL_SCANCODE_S])
	{
		if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.y -= 0.09;
			sprintCount++;
			slog("sprint backward");
		}
		
		else
		{
			self->position.y -= 0.05;
			slog("backward");
		}
	}

	if (keys[SDL_SCANCODE_D])
	{
		if (keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0)
		{
			self->position.x += 0.09;
			sprintCount++;
			slog("sprint right");
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

	if (keys[SDL_SCANCODE_SPACE] && self->position.z == 8 && jump == 0 && delayJump == 0)
	{
		//self->position.z += 15;
		jump = 2;
		slog("jumping");
	}

	if (jump == 2 && self->position.z < 23)
	{
		self->position.z += 0.1;
	}

	if (self->position.z >= 23)
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
			self->position.z -= 0.015;
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

	if (dash == 1 && ((self->position.y - beforeD) < 30))
	{
		self->position.y += 0.1;
	}

	if (self->position.y - beforeD >= 30)
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

	if (sidestep1 == 1 && ((self->position.x - beforeSS) > -15))
	{
		self->position.x -= 0.1;
	}

	if (self->position.x - beforeSS <= -15)
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

	if (sidestep2 == 1 && ((self->position.x - beforeSS) < 15))
	{
		self->position.x += 0.1;
	}

	if (self->position.x - beforeSS >= 15)
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