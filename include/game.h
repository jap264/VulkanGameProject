#ifndef __GAME_H__
#define __GAME_H__

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

typedef struct Game_S
{
	Uint32	bufferFrame;
	VkCommandBuffer commandBuffer;

}GameManager;

Uint32 get_bufferframe();

VkCommandBuffer get_commandbuffer();
#endif