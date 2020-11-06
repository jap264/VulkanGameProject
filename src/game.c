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
#include "enemy_cone.h"
#include "enemy_cube.h"
#include "enemy_brick.h"
#include "enemy_cylinder.h"
#include "enemy_sphere.h"

int main(int argc,char *argv[])
{
    int done = 0;
	int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;

	Entity *playerEnt = NULL;
	Player *player;

	Entity *world = NULL;

	//Enemies

    
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
        1600,                   //screen width
        1000,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
	slog_sync();

	
	gf3d_entity_init(1024);

    // main game loop
	slog("gf3d main loop begin");
	
	//player spawn
	player_init();
	player = get_player();
	playerEnt = get_player_entity();

	//world spawn
	world = gf3d_entity_new();
	world->model = gf3d_model_load("world");

	//brick spawn
	//brick_init();

	//cone spawn
	cone_init();

	//cube spawn
	//cube_init();

	//cylinder spawn
	//cylinder_init();

	//sphere spawn
	/*sphere_init();*/

	Vector3D camera_rotation = playerEnt->position;

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
		
		gf3d_entity_think_all(); //CALLS ALL THINK FUNCTIONS
		
		if (keys[SDL_SCANCODE_LEFT]) camera_rotation.x -= 0.001; //fix camera rotation
		if (keys[SDL_SCANCODE_RIGHT])  camera_rotation.x += 0.001;

		//if (keys[SDL_SCANCODE_LEFT]) cylinder_init();

		gf3d_vgraphics_thirdperson_camera(playerEnt->position);

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(),bufferFrame);
            commandBuffer = gf3d_command_rendering_begin(bufferFrame);

				gf3d_entity_draw_all(bufferFrame, commandBuffer);
                
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
