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
#include "gf3d_sprite.h"
#include "gfc_audio.h"

#include "player.h"
#include "sounds.h"
#include "powerup.h"
#include "enemy_cone.h"
#include "enemy_cube.h"
#include "enemy_brick.h"
#include "enemy_cylinder.h"
#include "enemy_sphere.h"

static int integer(float f)
{
	int result = f;
	return result;
}

static int randNum()
{
	return integer(gfc_crandom() * 5 + 5);
}

int main(int argc,char *argv[])
{
    int done = 0;
	int a;
    Uint8 validate = 0;
	float frame = 0;
    const Uint8 * keys;
    Uint32 bufferFrame = 0;
    VkCommandBuffer commandBuffer;

	Model *model = NULL;
	Matrix4 modelMat;

	Entity *playerEnt = NULL;
	Player *player;

	Entity *world = NULL;

	int spawnDelay = 0;

	int gameOn = 0;
    
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

	//Sounds
	sounds_init();
	sounds_play_gamesound();

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

	//spikebox spawn
	spikebox_init(vector3d(50, 50, 8));

	//hidebox spawn
	hidebox_init(vector3d(-50, -50, 8));

	//telebox spawn
	telebox_init(vector3d(50, -50, 12));

    while(!done)
    {
		if (spawnDelay > 0) spawnDelay -= 1;

		SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        //update game things here
		
		gf3d_entity_think_all(); //CALLS ALL THINK FUNCTIONS
		
		if (keys[SDL_SCANCODE_RETURN] && gameOn == 0)
		{
			if (player->status == 0)
			{
				player_respawn(player);
				playerEnt = get_player_entity();
			}

			gameOn = 1; //start spawning enemies
			slog("Good Luck!");
		}

		if (player->status == 0) gameOn = 0; //player dies, stop spawning entities

		if (gameOn == 1 && spawnDelay == 0)
		{
			int rand = randNum(); //picks a rand num 0-9

			if (rand < 2)
			{
				brick_init();
				spawnDelay = 3000;
			}

			else if (rand == 2 || rand == 3)
			{
				cone_init();
				spawnDelay = 3000;
			}

			else if (rand == 4 || rand == 5)
			{
				cube_init();
				spawnDelay = 3000;
			}

			else if (rand == 6 || rand == 7)
			{
				cylinder_init();
				spawnDelay = 3000;
			}

			else
			{
				sphere_init();
				spawnDelay = 3000;
			}
		}

		//manual enemy spawn
		if (keys[SDL_SCANCODE_1] && spawnDelay == 0)
		{
			brick_init();
			spawnDelay = 1000;
			slog("brick spawn");
		}

		if (keys[SDL_SCANCODE_2] && spawnDelay == 0)
		{
			cone_init();
			spawnDelay = 1000;
			slog("cone spawn");
		}
		
		if (keys[SDL_SCANCODE_3] && spawnDelay == 0)
		{
			cube_init();
			spawnDelay = 1000;
			slog("cube spawn");
		}
		
		if (keys[SDL_SCANCODE_4] && spawnDelay == 0)
		{
			sphere_init();
			spawnDelay = 1000;
			slog("sphere spawn");
		}
		
		if (keys[SDL_SCANCODE_5] && spawnDelay == 0)
		{
			cylinder_init();
			spawnDelay = 1000;
			slog("cylinder spawn");
		}

		//manual powerup spawn
		if (keys[SDL_SCANCODE_6] && spawnDelay == 0)
		{
			powerup_health();
			spawnDelay = 1000;
			slog("health powerup spawn");
		}

		if (keys[SDL_SCANCODE_7] && spawnDelay == 0)
		{
			powerup_speed();
			spawnDelay = 1000;
			slog("speed powerup spawn");
		}

		if (keys[SDL_SCANCODE_8] && spawnDelay == 0)
		{
			powerup_jump();
			spawnDelay = 1000;
			slog("jump powerup spawn");
		}

		if (keys[SDL_SCANCODE_9] && spawnDelay == 0)
		{
			powerup_invincibility();
			spawnDelay = 1000;
			slog("invincibility powerup spawn");
		}

		if (keys[SDL_SCANCODE_0] && spawnDelay == 0)
		{
			powerup_nuke();
			spawnDelay = 1000;
			slog("nuke powerup spawn");
		}

		//manual respawn
		if (keys[SDL_SCANCODE_BACKSPACE] && player->status == 0 && spawnDelay == 0)
		{
			player_respawn(player);
			playerEnt = get_player_entity();
		}

		gf3d_vgraphics_thirdperson_camera(playerEnt->position);

		// configure render command for graphics command pool
		// for each mesh, get a command and configure it from the pool
		bufferFrame = gf3d_vgraphics_render_begin();
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(), bufferFrame);
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
