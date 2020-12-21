#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "gf3d_entity.h"

typedef struct Explosion_S
{
	Entity *ent;

}Explosion;

/*
*	@brief allocates memory for explosion entity
*	@param position location for box to be spawned
*/
void explosion_init(Vector3D position);

/*
*	@brief initializes the explosion entity
*/
Entity *explosion_new();

/*
*	@brief called once per frame to update explosion state
*	@param self the explosion that is being updated
*/
void explosion_think(Entity *self);

/*
*	@brief frees the explosion entity to reused in the system
*	@param explosion for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void explosion_free(Explosion *explosion);

/*
*	@brief returns the explosion's entity
*/
Entity *get_explosion_entity();

/*
*	@brief returns the explosion
*/
Explosion *get_explosion();

#endif