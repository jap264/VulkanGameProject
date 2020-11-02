#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_entity.h"

void player_think(Entity *self);
void cube_think(Entity *self);
Entity *player = NULL;
int delayD = 0;
int delaySS = 0;
int delayJump = 0;
double beforeD;
double beforeSS;
int dash = 0;
int sidestep1 = 0;
int sidestep2 = 0;
int jump = 0;
int sprintCount = 0;
int sprintCheck = 0;

/**
*@brief have an entity follow another entity
*@param self the entity that is following
*@param other the entity that is being followed
*/
void follow(Entity *self, Entity *other);

int main(int argc,char *argv[])
{
    int done = 0;
	int a, i;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    //Model *model;
    //Matrix4 modelMat;
    //Model *model2;
    //Matrix4 modelMat2;
	Entity *cube = NULL;

    
    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
	slog_sync();

	
	gf3d_entity_init(1024);

    // main game loop
	slog("gf3d main loop begin");

		player = gf3d_entity_new();
		cube = gf3d_entity_new();

		player->model = gf3d_model_load("dino");
		player->think = player_think;

		cube->model = gf3d_model_load("cube");
		cube->think = cube_think;

		/*
		gfc_matrix_make_translation(
			ent->modelMatrix,
			vector3d(gfc_crandom() * 5, gfc_crandom() * 5, gfc_crandom() * 5));
		gfc_matrix_rotate(
			ent->modelMatrix,
			ent->modelMatrix,
			gfc_crandom()*0.01,
			vector3d(gfc_crandom(), gfc_crandom(), gfc_crandom()));
		*/

	
	/*model = gf3d_model_load("dino");
	gfc_matrix_identity(modelMat);
	model2 = gf3d_model_load("dino");
    gfc_matrix_identity(modelMat2);
    gfc_matrix_make_translation(
            modelMat2,
            vector3d(10,0,0)
        );*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
		
		gf3d_entity_think_all(); //CALLS ALL THINK FUNCTIONS (UNCOMMENT HERE)
		
        /*gfc_matrix_rotate(
            modelMat2,
            modelMat2,
            0.002,
            vector3d(0,0,1));*/

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
            commandBuffer = gf3d_command_rendering_begin(bufferFrame);

				gf3d_entity_draw_all(bufferFrame, commandBuffer);
				//gf3d_model_draw(model,bufferFrame,commandBuffer,modelMat);
                //gf3d_model_draw(model2,bufferFrame,commandBuffer,modelMat2);
                
            gf3d_command_rendering_end(commandBuffer);
            
        gf3d_vgraphics_render_end(bufferFrame);

        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

void player_think(Entity *self)
{
	//gf3d_vgraphics_rotate_camera(0.001);
	/*gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.002,
		vector3d(1, 0, 0));
	*/

	if (delayD > 0)
	{
		delayD--;
		//slog("%i", delayD);
	}

	if (delaySS > 0)
	{
		delaySS--;
		//slog("%i", delaySS);
	}
	
	if (delayJump > 0)
	{
		delayJump--;
		//slog("%i", delaySS);
	}

	if (sprintCount >= 5000)
	{
		sprintCheck = 1;
	}

	if (sprintCheck == 1)
	{
		sprintCount--;
		if (sprintCount <= 0)
		{
			sprintCheck = 0;
		}
	}

	const Uint8 *keys;
	SDL_PumpEvents();
	keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W])
	{
		self->position.y += 0.05;
		slog("y position +");
	}

	if (keys[SDL_SCANCODE_A])
	{
		self->position.x -= 0.05;
		slog("x position -");
	}

	if (keys[SDL_SCANCODE_S])
	{
		self->position.y -= 0.05;
		slog("y position -");
	}

	if (keys[SDL_SCANCODE_D])
	{
		self->position.x += 0.05;
		slog("x position +");
	}
	
	if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0 && self->position.z == 0)
	{
		self->position.y += 0.08;
		sprintCount++;
		slog("sprinting");
	}

	if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0 && self->position.z == 0)
	{
		self->position.x -= 0.08;
		sprintCount++;
		slog("sprinting");
	}

	if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0 && self->position.z == 0)
	{
		self->position.y -= 0.05;
		sprintCount++;
		slog("sprinting");
	}

	if (keys[SDL_SCANCODE_D] && keys[SDL_SCANCODE_LSHIFT] && sprintCheck == 0 && self->position.z == 0)
	{
		self->position.x += 0.08;
		sprintCount++;
		slog("sprinting");
	}

	if (keys[SDL_SCANCODE_SPACE] && self->position.z == 0 && jump == 0 && delayJump == 0)
	{
		//self->position.z += 15;
		jump = 2;
		slog("jumping");
	}

	if (jump == 2 && self->position.z < 15)
	{
		self->position.z += 0.1;
	}

	if (self->position.z >= 15)
	{
		jump = 1;
		delayJump = 4500;
	}

	if (self->position.z > 0 && jump == 1)
	{
		if (keys[SDL_SCANCODE_SPACE])
		{
			self->position.z -= 0.008;
		}
		else
		{
			self->position.z -= 0.015;
		}
	}

	if (self->position.z <= 0)
	{
		self->position.z = 0;
		jump = 0;
	}

	if (keys[SDL_SCANCODE_F] && delayD == 0)
	{
		delayD = 3000;
		dash = 1;
		beforeD = self->position.y;
		//self->position.y += 30;
		slog("dashed");
	}
	
	if (dash == 1 && ((self->position.y - beforeD) < 30))
	{
		self->position.y += 0.1;
	}

	if (self->position.y - beforeD >= 30)
	{
		dash = 0;
	}
	
	//if (keys[SDL_SCANCODE_A] && keys[SDL_SCANCODE_LALT]) slog("%i", delaySS);

	if (keys[SDL_SCANCODE_Q] && delaySS == 0)
	{
		delaySS = 2000;
		sidestep1 = 1;
		beforeSS = self->position.x;
		//self->position.x -= 15;
		slog("sidestep1");
	}

	if (sidestep1 == 1 && ((self->position.x - beforeSS) > -15))
	{
		self->position.x -= 0.1;
	}

	if (self->position.x - beforeSS <= -15)
	{
		sidestep1 = 0;
	}

	if (keys[SDL_SCANCODE_E] && delaySS == 0)
	{
		delaySS = 2000;
		sidestep2 = 1;
		beforeSS = self->position.x;
		//self->position.x += 15;
		slog("sidestep2");
	}

	if (sidestep2 == 1 && ((self->position.x - beforeSS) < 15))
	{
		self->position.x += 0.1;
	}

	if (self->position.x - beforeSS >= 15)
	{
		sidestep2 = 0;
	}

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
	);
}

void follow(Entity *self, Entity *other)
{
	if (!self || !other) return;

	if (self->position.y > other->position.y)
	{
		self->position.y -= 0.015;
		//slog("following -y");
	}
	
	if (self->position.y < other->position.y)
	{
		self->position.y += 0.015;
		//slog("following +y");
	}
	if (self->position.x > other->position.x)
	{
		self->position.x -= 0.015;
		//slog("following -x");
	}
	
	if (self->position.x < other->position.x)
	{
		self->position.x += 0.015;
		//slog("following +x");
	}

	gfc_matrix_make_translation(
		self->modelMatrix,
		self->position
	);
}

void cube_spawn()
{
	Entity *new = NULL;

	
}
void cube_think(Entity *self)
{
	if (!self) return;
	follow(self, player);
	gfc_matrix_rotate(
		self->modelMatrix,
		self->modelMatrix,
		0.002,
		vector3d(1, 0, 0));
	
}

void sphere_think(Entity *self)
{
	if (!self) return;
}

void brick_think(Entity *self)
{
	if (!self) return;
}

void cone_think(Entity *self)
{
	if (!self) return;
}

void cylinder_think(Entity *self)
{
	if (!self) return;
}

/*eol@eof*/
