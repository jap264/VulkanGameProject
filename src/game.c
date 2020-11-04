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

#include "player.h"

int main(int argc,char *argv[])
{
    int done = 0;
	int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;
    //Model *model;
    //Matrix4 modelMat;
    //Model *model2;
    //Matrix4 modelMat2;

	Entity *playerEnt = NULL;
	Player *player;
	Entity *cube = NULL;
	Entity *world = NULL;
	Entity *cone = NULL;

	float rotation = 0;
    
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
	
	player_init();
	player = get_player();
	playerEnt = get_player_entity();
	//cube = gf3d_entity_new();

	playerEnt->model = gf3d_model_load("dino");
	playerEnt->think = player_think;

	world = gf3d_entity_new();
	world->model = gf3d_model_load("world");

	cone = gf3d_entity_new();
	cone->model = gf3d_model_load("cone");
	cone->position = vector3d(0, 0, 20);

	world->position = vector3d(0, 0, -10);

	gf3d_vgraphics_rotate_camera(-0.4, 1);

	//cube->model = gf3d_model_load("cube");
	//cube->think = sphere_think;

	//gf3d_camera_set_position(player->position);
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
		
		if (keys[SDL_SCANCODE_LEFT]) gf3d_vgraphics_rotate_camera(0.002, 3);
		if (keys[SDL_SCANCODE_RIGHT]) gf3d_vgraphics_rotate_camera(-0.002, 3);
		
		gf3d_vgraphics_thirdperson_camera(playerEnt->position);
		//gf3d_vgraphics_rotate_camera(rotation, 3);
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

/*eol@eof*/
