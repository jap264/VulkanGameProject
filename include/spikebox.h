#ifndef __SPIKEBOX_H__
#define __SPIKEBOX_H__

#include "gf3d_entity.h"

typedef struct Spikebox_S
{
	Entity *ent;

}Spikebox;

/*
*	@brief allocates memory for spikebox entity
*	@param position location for box to be spawned
*/
void spikebox_init(Vector3D *position);

/*
*	@brief initializes the spikebox entity
*/
Entity *spikebox_new();

/*
*	@brief called once per frame to update spikebox state
*	@param self the spikebox that is being updated
*/
void spikebox_think(Entity *self);

/*
*	@brief frees the spikebox entity to reused in the system
*	@param spikebox for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void spikebox_free(Spikebox *spikebox);

/*
*	@brief returns the spikebox's entity
*/
Entity *get_spikebox_entity();

/*
*	@brief returns the spikebox
*/
Spikebox *get_spikebox();

#endif