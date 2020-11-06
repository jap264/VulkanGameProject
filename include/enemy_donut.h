#ifndef __ENEMY_DONUT_H__
#define __ENEMY_DONUT_H__

#include "gf3d_entity.h"

typedef struct Donut_S
{
	Entity *ent;

}Donut;

/*
*	@brief allocates memory for donut entity
*/
void donut_init();

/*
*	@brief initializes the donut entity
*/
Entity *donut_new();

/*
*	@brief called once per frame to update donut state
*	@param self the donut that is being updated
*/
void donut_think(Entity *self);

/*
*	@brief frees the donut entity to reused in the system
*	@param donut for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void donut_free(Donut *donut);

/*
*	@brief returns the donut's entity
*/
Entity *get_donut_entity();

/*
*	@brief returns the donut
*/
Donut *get_donut();

#endif