/*
 * player.h
 *
 *  Created on: Nov 26, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include "fw.h"

void player_init();
void player_placement(long x, long y, long z);
void player_on_level(short lvl);
inline void player_update();
inline void player_render();
inline int player_dead();
aabb_t* player_getaabb();

#endif /*PLAYER_H_*/
