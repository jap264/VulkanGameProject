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

void dino_think(Entity *self); 

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
	Entity *ent = NULL;

    
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

		ent = gf3d_entity_new();

		ent->model = gf3d_model_load("dino");
		ent->think = dino_think;

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

void dino_think(Entity *self)
{
		/*gf3d_vgraphics_rotate_camera(0.001);
		gfc_matrix_rotate(
			self->modelMatrix,
			self->modelMatrix,
			0.002,
			vector3d(1, 0, 0));
		*/
		const Uint8 * keys;
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
		
		gfc_matrix_make_translation(
			self->modelMatrix,
			self->position
		);
}

void cube_think(Entity self)
{

}

void sphere_think(Entity self)
{

}

void brick_think(Entity self)
{

}

void cone_think(Entity self)
{

}

void cylinder_think(Entity self)
{

}

/*eol@eof*/
