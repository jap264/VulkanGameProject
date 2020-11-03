#ifndef __PLAYER_H__
#define __PLAYER_H

#include "gf3d_entity.h"

typedef struct Player_S
{
	Entity *ent;

}Player;

/*
*	@brief allocates memory for player entity
*/
void player_init();

/*
*	@brief initializes the player entity
*/
Entity *player_new();

/*
*	@brief called once per frame to update player state
*	@param self the player that is being updated
*/
void player_think(Entity *self);

/*
*	@brief frees the player entity to reused in the system
*	@param player for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void player_free(Player *player);

/*
*	@brief returns the player's entity
*/
Entity *get_player_entity();

/*
*	@brief returns the player
*/
Player *get_player();

#endif