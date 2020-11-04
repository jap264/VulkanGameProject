#ifndef __ENEMY_CUBE_H__
#define __ENEMY_CUBE_H__

#include "gf3d_entity.h"

typedef struct Cube_S
{
	Entity *ent;

}Cube;

/*
*	@brief allocates memory for cube entity
*/
void cube_init();

/*
*	@brief initializes the cube entity
*/
Entity *cube_new();

/*
*	@brief called once per frame to update cube state
*	@param self the cube that is being updated
*/
void cube_think(Entity *self);

/*
*	@brief frees the cube entity to reused in the system
*	@param cube for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void cube_free(Cube *cube);

/*
*	@brief returns the cube's entity
*/
Entity *get_cube_entity();

/*
*	@brief returns the cube
*/
Cube *get_cube();

#endif