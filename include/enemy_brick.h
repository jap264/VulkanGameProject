#ifndef __ENEMY_BRICK_H__
#define __ENEMY_BRICK_H__

#include "gf3d_entity.h"

typedef struct Brick_S
{
	Entity *ent;

}Brick;

/*
*	@brief allocates memory for brick entity
*/
void brick_init();

/*
*	@brief initializes the brick entity
*/
Entity *brick_new();

/*
*	@brief called once per frame to update brick state
*	@param self the brick that is being updated
*/
void brick_think(Entity *self);

/*
*	@brief frees the brick entity to reused in the system
*	@param brick for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void brick_free(Brick *brick);

/*
*	@brief returns the brick's entity
*/
Entity *get_brick_entity();

/*
*	@brief returns the brick
*/
Brick *get_brick();

#endif