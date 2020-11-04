#ifndef __ENEMY_CONE_H__
#define __ENEMY_CONE_H__

#include "gf3d_entity.h"

typedef struct Cone_S
{
	Entity *ent;

}Cone;

/*
*	@brief allocates memory for cone entity
*/
void cone_init();

/*
*	@brief initializes the cone entity
*/
Entity *cone_new();

/*
*	@brief called once per frame to update cone state
*	@param self the cone that is being updated
*/
void cone_think(Entity *self);

/*
*	@brief frees the cone entity to reused in the system
*	@param cone for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void cone_free(Cone *cone);

/*
*	@brief returns the cone's entity
*/
Entity *get_cone_entity();

/*
*	@brief returns the cone
*/
Cone *get_cone();

#endif