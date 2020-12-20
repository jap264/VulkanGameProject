#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gf3d_entity.h"

typedef struct Player_S
{
	Entity *ent;
	int		health;
	int		maxHealth;
	int		status;
	int		hiding;
	int		points;
	int		combo;
	int		enemiesKilled;

}Player;

/*
*	@brief allocates memory for player entity
*/
void player_init();

/*
*	@brief respawns the player entity
*/
void player_respawn(Player *player);

/*
*	@brief player dies
*/
void player_die();

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
*	@brief checks what the player collided with and respond accordingly
*	@param other sthe entity the player collided with
*/
void player_collide(Entity *other);

/*
*	@brief returns the player's entity
*/
Entity *get_player_entity();

/*
*	@brief returns the player
*/
Player *get_player();

/*
*	@brief returns the player's health
*/
int *get_player_health();

#endif