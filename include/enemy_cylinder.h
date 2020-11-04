#ifndef __ENEMY_CYLINDER_H__
#define __ENEMY_CYLINDER_H__

#include "gf3d_entity.h"

typedef struct Cylinder_S
{
	Entity *ent;

}Cylinder;

/*
*	@brief allocates memory for cylinder entity
*/
void cylinder_init();

/*
*	@brief initializes the cylinder entity
*/
Entity *cylinder_new();

/*
*	@brief called once per frame to update cylinder state
*	@param self the cylinder that is being updated
*/
void cylinder_think(Entity *self);

/*
*	@brief frees the cylinder entity to reused in the system
*	@param cylinder for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void cylinder_free(Cylinder *cylinder);

/*
*	@brief returns the cylinder's entity
*/
Entity *get_cylinder_entity();

/*
*	@brief returns the cylinder
*/
Cylinder *get_cylinder();

#endif