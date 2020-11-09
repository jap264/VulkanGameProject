#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "gf3d_entity.h"

typedef struct Powerup_S
{
	Entity *ent;

}Powerup;

/*
*	@brief allocates memory for powerup entity
*/
void powerup_init();

/*
*	@brief initializes the powerup entity
*/
Entity *powerup_new();

/*
*	@brief called once per frame to update powerup state
*	@param self the powerup that is being updated
*/
void powerup_think(Entity *self);

/*
*	@brief frees the powerup entity to reused in the system
*	@param powerup for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void powerup_free(Powerup *powerup);

/*
*	@brief returns the powerup's entity
*/
Entity *get_powerup_entity();

/*
*	@brief returns the powerup
*/
Powerup *get_powerup();

#endif