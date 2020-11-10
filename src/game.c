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
#include "powerup.h"
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

	int spawnDelay = 0;
    
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
	
	//player spawn
	player_init();
	player = get_player();
	playerEnt = get_player_entity();

	//world spawn
	world = gf3d_entity_new();
	world->model = gf3d_model_load("world");
	world->radius = 0;

	//powerup_init();

	Vector3D camera_rotation = playerEnt->position;

    while(!done)
    {
		if (spawnDelay > 0) spawnDelay -= 1;
		
		SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
		
		gf3d_entity_think_all(); //CALLS ALL THINK FUNCTIONS
		
		if (keys[SDL_SCANCODE_LEFT]) camera_rotation.x -= 0.001; //fix camera rotation
		if (keys[SDL_SCANCODE_RIGHT])  camera_rotation.x += 0.001;

		//manual enemy spawn
		if (keys[SDL_SCANCODE_1] && spawnDelay == 0)
		{
			brick_init();
			spawnDelay = 3000;
			slog("brick spawn");
		}

		if (keys[SDL_SCANCODE_2] && spawnDelay == 0)
		{
			cone_init();
			spawnDelay = 3000;
			slog("cone spawn");
		}
		
		if (keys[SDL_SCANCODE_3] && spawnDelay == 0)
		{
			cube_init();
			spawnDelay = 3000;
			slog("cube spawn");
		}
		
		if (keys[SDL_SCANCODE_4] && spawnDelay == 0)
		{
			cylinder_init();
			spawnDelay = 3000;
			slog("cylinder spawn");
		}
		
		if (keys[SDL_SCANCODE_5] && spawnDelay == 0)
		{
			sphere_init();
			spawnDelay = 3000;
			slog("sphere spawn");
		}

		if (keys[SDL_SCANCODE_6] && spawnDelay == 0)
		{
			powerup_health();
			spawnDelay = 3000;
			slog("health powerup spawn");
		}

		if (keys[SDL_SCANCODE_7] && spawnDelay == 0)
		{
			powerup_speed();
			spawnDelay = 3000;
			slog("speed powerup spawn");
		}

		if (keys[SDL_SCANCODE_8] && spawnDelay == 0)
		{
			powerup_jump();
			spawnDelay = 3000;
			slog("jump powerup spawn");
		}

		if (keys[SDL_SCANCODE_9] && spawnDelay == 0)
		{
			powerup_invincibility();
			spawnDelay = 3000;
			slog("invincibility powerup spawn");
		}

		if (keys[SDL_SCANCODE_0] && spawnDelay == 0)
		{
			powerup_nuke();
			spawnDelay = 3000;
			slog("nuke powerup spawn");
		}

		if (keys[SDL_SCANCODE_RETURN] && player->status == 0)
		{
			player_init();
			playerEnt = get_player_entity();
		}

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
