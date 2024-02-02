/*
 * enemy.h
 *
 *  Created on: Jan 19, 2024
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "fw.h"

#define ENEMY_MAX_AMOUNT 4

void enemy_init();
void enemy_placement(short index, short starting_index, long x, long y, long z);
void enemy_set_node(short enemy_index, short index, long x, long y, long z);
void enemy_set_actives(short i);
inline void enemy_update();
inline void enemy_render();
inline int enemy_on_player();

#endif /* ENEMY_H_ */
