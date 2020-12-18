#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include "gfc_audio.h"

typedef struct
{
	Sound *_game;
	Sound *_playerhit;
	Sound *_enemyhit;
	Sound *_teleport;
	Sound *_doground;
}Sounds;
/*
 * @brief allocates memory for the sounds
 */
void sounds_init();

/*
* @brief plays player hit sound
*/
void sounds_play_gamesound();

/*
* @brief plays player hit sound
*/
void sounds_play_playerhit();

/*
* @brief plays enemy hit sound
*/
void sounds_play_enemyhit();

/*
* @brief plays spikebox hit sound
*/
void sounds_play_teleport();

/*
* @brief plays dog round sount
*/
void sounds_play_doground();
#endif