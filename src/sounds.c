#include <SDL.h> 

#include "simple_logger.h"
#include "sounds.h"
#include "gfc_audio.h"

static Sounds *sounds = { 0 };

void sounds_init()
{
	gfc_audio_init(10, 1, 1, 3, 1, 1);
	
	sounds = (Sounds *)gfc_allocate_array(sizeof(Sounds), 1);
	
	sounds->_game = gfc_sound_load("sounds/game.wav", 1, 0);
	sounds->_playerhit = gfc_sound_load("sounds/playerHit.wav", 1, 0);
	sounds->_enemyhit = gfc_sound_load("sounds/enemyHit.wav", 1, 0);
	sounds->_teleport = gfc_sound_load("sounds/teleport.wav", 1, 0);
}

void sounds_play_gamesound()
{
	gfc_sound_play(sounds->_game, -1, 1, -1, -1);
}

void sounds_play_playerhit()
{
	gfc_sound_play(sounds->_playerhit, 0, 1, 2, -1);
}

void sounds_play_enemyhit()
{
	gfc_sound_play(sounds->_enemyhit, 0, 1, 3, -1);
}

void sounds_play_teleport()
{
	gfc_sound_play(sounds->_teleport, 0, 1, 4, -1);
}