#include <SDL.h> 

#include "simple_logger.h"

#include "gf3d_camera.h"
#include "gf3d_vgraphics.h"
#include "gfc_matrix.h"
#include "gf3d_model.h"
#include "gfc_vector.h"

#include "enemy_dog.h"
#include "sounds.h"
#include "player.h"
#include "gf3d_entity.h"

static Dog *dog = { 0 };
static float rotation = 0;
enum type{ _player, _powerup, _enemy, _spikebox, _hidebox, _telebox, _dog};

void dog_init()
{
	Dog *dog;
	Entity *dogEnt = NULL;
	dog = (Dog *)gfc_allocate_array(sizeof(Dog), 1);

	dog->ent = dog_new();
	gfc_word_cpy(dog->ent->name, "dog");
	dog->ent->type = _dog;
	dog->ent->position = vector3d(-10, 296, 8);
	gfc_matrix_make_translation(dog->ent->modelMatrix, dog->ent->position);
	dog->ent->velocity = vector3d(0, 0, 0);
	dog->ent->rotation = vector3d(0, 0, 0);
	dog->ent->radius = 10;

	dog->ent->model = gf3d_model_load("dog");
	dog->ent->think = dog_think;
	dog->ent->die = dog_free;
}

void dog_spawn(Vector3D position)
{
	Dog *dog;
	Entity *dogEnt = NULL;
	dog = (Dog *)gfc_allocate_array(sizeof(Dog), 1);

	dog->ent = dog_new();
	gfc_word_cpy(dog->ent->name, "dog");
	dog->ent->type = _dog;
	dog->ent->position = position;
	gfc_matrix_make_translation(dog->ent->modelMatrix, dog->ent->position);
	dog->ent->velocity = vector3d(0, 0, 0);
	dog->ent->rotation = vector3d(0, 0, 0);
	dog->ent->radius = 10;

	dog->ent->model = gf3d_model_load("dog");
	dog->ent->model->frameCount = 2;
	dog->ent->think = dog_think;
	dog->ent->die = dog_free;
}

void dog_round()
{
	sounds_play_doground();
	dog_spawn(vector3d(-295, 0, 8));
	dog_spawn(vector3d(295, 0, 8));
	dog_spawn(vector3d(0, -300, 8));
	dog_spawn(vector3d(0, 285, 8));
}

Entity *dog_new()
{
	return gf3d_entity_new();
}

void dog_free(Dog *dog)
{
	if (!dog) return;

	gf3d_entity_free(dog->ent);
	memset(dog, 0, sizeof(Dog));
}

void dog_think(Entity *self)
{
	if (!self) return;
	follow(self, get_player_entity(), 0.045);
	
	if (self->position.z - 5 > get_player_entity()->position.z)
	{
		self->position.z -= 0.035;
	}

	if (self->position.z - 5 < get_player_entity()->position.z)
	{
		self->position.z += 0.035;
	}

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
		);

	rotation -= 0.001;

	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		rotation,
		vector3d(1, 1, 1));
}

Entity *get_dog_entity()
{
	return dog->ent;
}

Dog *get_dog()
{
	return dog;
}