#ifndef __ENEMY_SPHERE_H__
#define __ENEMY_SPHERE_H__

#include "gf3d_entity.h"

typedef struct Sphere_S
{
	Entity *ent;

}Sphere;

/*
*	@brief allocates memory for sphere entity
*/
void sphere_init();

/*
*	@brief initializes the sphere entity
*/
Entity *sphere_new();

/*
*	@brief called once per frame to update sphere state
*	@param self the sphere that is being updated
*/
void sphere_think(Entity *self);

/*
*	@brief frees the sphere entity to reused in the system
*	@param sphere for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void sphere_free(Sphere *sphere);

/*
*	@brief returns the sphere's entity
*/
Entity *get_sphere_entity();

/*
*	@brief returns the sphere
*/
Sphere *get_sphere();

#endif