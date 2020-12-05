#include "simple_logger.h"

#include "gf3d_entity.h"
#include "player.h"
#include "powerup.h"

typedef struct
{
	Entity *entity_list;	/*list of entities*/
	Uint32 entity_count;	/*upper limit for concurrent active entities*/
} EntityManager;

static EntityManager gf3d_entity = { 0 };

void gf3d_entity_free(Entity *entity);

enum type{ _player, _powerup, _enemy };

Entity  *gf3d_entity_get_list()
{
	return gf3d_entity.entity_list;
}

Uint32  *gf3d_entity_get_entity_count()
{
	return gf3d_entity.entity_count;
}

void gf3d_entity_close()
{
	int i;
	if (gf3d_entity.entity_list != NULL)
	{
		for (i = 0; i < gf3d_entity.entity_count; i++)
		{	
			gf3d_entity_free(&gf3d_entity.entity_list[i]);
		}
		free(gf3d_entity.entity_list);
	}
	memset(&gf3d_entity, 0, sizeof(EntityManager));
	slog("Entity System Closed");
}

void gf3d_entity_init(Uint32 maxEntities)
{
	if (gf3d_entity.entity_list != NULL)
	{
		slog("WARNING: entity systrem already initialized");
		return;
	}

	gf3d_entity.entity_list = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (!gf3d_entity.entity_list)
	{
		slog("failed to allocate entity list");
		return;
	}
	gf3d_entity.entity_count = maxEntities;
	atexit(gf3d_entity_close);
	slog("Entity System Initialized");
}

void gf3d_entity_free(Entity *entity)
{
	if (!entity)return;
	//gf3d_model_free(entity->model);
	memset(entity, 0, sizeof(Entity));
}

Entity  *gf3d_entity_new()
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse)
		{
			gf3d_entity.entity_list[i]._inuse = 1;
			gfc_matrix_identity(gf3d_entity.entity_list[i].modelMatrix);
			return &gf3d_entity.entity_list[i];
		}
	}
	slog("Failed to provide new entity, no unused slots");
	return NULL;
}

int checkCollision(Entity *self, Entity *other)
{
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;
	float distance_z = self->position.z - other->position.z;

	if (self->radius == 0 || other->radius == 0) return 0;
	//slog("%f, %f", self->radius, other->radius);

	float radii_sum = self->radius + other->radius;

	if ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) <= (radii_sum * radii_sum)) return 1;

	return 0;
}

void gf3d_entity_think(Entity *self)
{
	if (!self)return;
	if (!self->think)return; //no think function to call
	self->think(self);
}

void gf3d_entity_think_all()
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse) continue;
		gf3d_entity_think(&gf3d_entity.entity_list[i]);

		//write check collisions here
		for (int x = 0; x < gf3d_entity.entity_count; x++)
		{
			if (&gf3d_entity.entity_list[x] == &gf3d_entity.entity_list[i]) continue;
			if (!&gf3d_entity.entity_list[x] || !&gf3d_entity.entity_list[i])
			{
				slog("null entities");
				continue;
			}

			//check collision
			if (checkCollision(&gf3d_entity.entity_list[x], &gf3d_entity.entity_list[i]) == 1)
			{
				//slog("%s has collided with %s", &gf3d_entity.entity_list[x].name, &gf3d_entity.entity_list[i].name);

				if (&gf3d_entity.entity_list[x] == get_player_entity()) //first entity is player
				{
					//slog("x is the player");
					player_collide(&gf3d_entity.entity_list[i]);
				}
				
				else if (&gf3d_entity.entity_list[i] == get_player_entity()) //second entity is the player
				{
					//slog("i is the player");
					player_collide(&gf3d_entity.entity_list[x]);
				}

				else if (gf3d_entity.entity_list[x].type == 1 || // ignore collisions between powerups vs. other powerups & enemies
					gf3d_entity.entity_list[i].type == 1 ||
					gf3d_entity.entity_list[x].type == 4 || //ignore collisions between hidebox vs. enemies
					gf3d_entity.entity_list[i].type == 4 ||
					gf3d_entity.entity_list[x].type == 5 || //ignore collisions between telebox vs. enemies
					gf3d_entity.entity_list[i].type == 5) continue;

				else if (gf3d_entity.entity_list[x].type == 3) //if spikebox collides with an enemy
				{
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
					get_player()->points += 1;
				}

				else if (gf3d_entity.entity_list[i].type == 3) //if spikebox collides with an enemy
				{
					gf3d_entity_free(&gf3d_entity.entity_list[x]);
					get_player()->points += 1;
				}

				else //two enemies colliding
				{
					slog("two enemies have collided");
					/*slog("x ent type: %i", &gf3d_entity.entity_list[x].type);
					slog("i ent type: %i", &gf3d_entity.entity_list[i].type);*/
					gf3d_entity_free(&gf3d_entity.entity_list[x]); 
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
					powerup_init();
					get_player()->points += 2;
				}
			}
		}
	}
}

void gf3d_entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	if (!self)return;
	if (!self->model) return;
	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMatrix);
}

void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse) continue;
		gf3d_entity_draw(&gf3d_entity.entity_list[i], bufferFrame, commandBuffer);
	}
}

void gf3d_entity_kill(Entity *entity)
{
	gf3d_entity.entity_count--;
	entity->_inuse = 0;
}

void follow(Entity *self, Entity *other, float speed)
{
	if (!self || !other) return;

	if (self->position.y > other->position.y)
	{
		self->position.y -= speed;
		//slog("following -y");
	}

	if (self->position.y < other->position.y)
	{
		self->position.y += speed;
		//slog("following +y");
	}
	if (self->position.x > other->position.x)
	{
		self->position.x -= speed;
		//slog("following -x");
	}

	if (self->position.x < other->position.x)
	{
		self->position.x += speed;
		//slog("following +x");
	}

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
		);
}
/*eol@eof*/