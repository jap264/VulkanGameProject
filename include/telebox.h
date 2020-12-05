#ifndef __TELEBOX_H__
#define __TELEBOX_H__

#include "gf3d_entity.h"

typedef struct Telebox_S
{
	Entity *ent;

}Telebox;

/*
*	@brief allocates memory for telebox entity
*	@param position location for box to be spawned
*/
void telebox_init(Vector3D *position);

/*
*	@brief initializes the telebox entity
*/
Entity *telebox_new();

/*
*	@brief called once per frame to update telebox state
*	@param self the telebox that is being updated
*/
void telebox_think(Entity *self);

/*
*	@brief frees the telebox entity to reused in the system
*	@param telebox for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void telebox_free(Telebox *telebox);

/*
*	@brief returns the telebox's entity
*/
Entity *get_telebox_entity();

/*
*	@brief returns the telebox
*/
Telebox *get_telebox();

#endif