/*
 * crystals.h
 *
 *  Created on: Nov 26, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef CRYSTALS_H_
#define CRYSTALS_H_

#define CRYSTALS_MAX_AMOUNT 10

void crystals_init();
void crystals_placement(int index, int x, int y, int z, int value);
void crystals_set_actives(int i);
inline int  crystals_all_active();
inline void crystals_update();
inline void crystals_render();

#endif /* CRYSTALS_H_ */
