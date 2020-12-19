#ifndef __HIDEBOX_H__
#define __HIDEBOX_H__

#include "gf3d_entity.h"

typedef struct Hidebox_S
{
	Entity *ent;

}Hidebox;

/*
*	@brief allocates memory for hidebox entity
*	@param position location for box to be spawned
*/
void hidebox_init(Vector3D position);

/*
*	@brief initializes the hidebox entity
*/
Entity *hidebox_new();

/*
*	@brief called once per frame to update hidebox state
*	@param self the hidebox that is being updated
*/
void hidebox_think(Entity *self);

/*
*	@brief frees the hidebox entity to reused in the system
*	@param hidebox for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void hidebox_free(Hidebox *hidebox);

/*
*	@brief returns the hidebox's entity
*/
Entity *get_hidebox_entity();

/*
*	@brief returns the hidebox
*/
Hidebox *get_hidebox();

#endif