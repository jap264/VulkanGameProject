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
*	@brief picks a random powerup type on a position
*	@param powerup the powerup to spawn
*/
void powerup_spawn(Powerup *powerup);

/*
*	@brief spawns a health powerup
*	@note adds +1 health if not max health (3)
*/
void powerup_health();

/*
*	@brief spawns a speed powerup
*	@note doubles speed in all areas
*/
void powerup_speed();

/*
*	@brief spawns a jump powerup
*	@note increase jump height, jump speed, and slow fall
*/
void powerup_jump();

/*
*	@brief spawns a invincibility powerup
*	@note player is immune to enemy attacks and enemies die on impact
*/
void powerup_invincibility();

/*
*	@brief spawns a nuke powerup
*	@note despawns all enemies
*/
void powerup_nuke();

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