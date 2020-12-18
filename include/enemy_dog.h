#ifndef __ENEMY_DOG_H__
#define __ENEMY_DOG_H__

#include "gf3d_entity.h"

typedef struct Dog_S
{
	Entity *ent;

}Dog;

/*
*	@brief allocates memory for dog entity
*/
void dog_init();

/*
*	@brief spawns a dog in a particular position in world space
*	@param position location to spawn the dog
*/
void dog_spawn(Vector3D position);

/*
*	@brief spawns 4 dogs
*/
void dog_round();

/*
*	@brief initializes the dog entity
*/
Entity *dog_new();

/*
*	@brief called once per frame to update dog state
*	@param self the dog that is being updated
*/
void dog_think(Entity *self);

/*
*	@brief frees the dog entity to reused in the system
*	@param dog for its entity to be freed
*	@note the pointer should be set to zero and no longer used.
*/
void dog_free(Dog *dog);

/*
*	@brief returns the dog's entity
*/
Entity *get_dog_entity();

/*
*	@brief returns the dog
*/
Dog *get_dog();

#endif