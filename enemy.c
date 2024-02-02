/*
 * enemy.c
 *
 *  Created on: Jan 20, 2024
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "enemy.h"
#include "player.h"

#include <libps.h>
#include "DATA.H"

static int current_active_enemies = 1;
obj_t      enemyobj[ENEMY_MAX_AMOUNT];
aabb_t     enemyaabb[ENEMY_MAX_AMOUNT];
VECTOR     vnodes[ENEMY_MAX_AMOUNT][11];
int        vstart[ENEMY_MAX_AMOUNT];
int        cnode[ENEMY_MAX_AMOUNT]; //current node
int        overlap = 0;
aabb_t*    pl_aabb;
VECTOR     enemysca={128, 128, 128}; //for scale of aabb

void enemy_init()
{
	int i;
	for(i = 0; i < ENEMY_MAX_AMOUNT; ++i)
	{
		obj_init(&enemyobj[i]);
		aabb_init(&enemyaabb[i], &enemyobj[i].transform.pos, &enemysca);
		load_model(&enemyobj[i], (long*)ENEMY_DATA);

		cnode[i] = 0;
	}

	pl_aabb = player_getaabb();
}

void enemy_placement(short index, short starting_index, long x, long y, long z)
{
	enemyobj[index].transform.pos.vx = x;
	enemyobj[index].transform.pos.vy = y;
	enemyobj[index].transform.pos.vz = z;

	cnode[index] = starting_index;
}

void enemy_set_node(short enemy_index, short index, long x, long y, long z)
{
	VECTOR tmp;
	tmp.vx = x;
	tmp.vy = y;
	tmp.vz = z;
	vnodes[enemy_index][index] = tmp;

	tmp.vy = -1; //same as '\0'
	vnodes[enemy_index][index + 1] = tmp;
}

void enemy_set_actives(short i)
{
	current_active_enemies = i;
}

inline void enemy_update()
{
	register int i;
	VECTOR curpos;

	overlap = 0;

	for(i = 0; i < current_active_enemies; ++i)
	{
		aabb_update(&enemyaabb[i], &enemyobj[i].transform.pos, &enemysca);
		enemyobj[i].transform.rot.vy += 52;

		/*Get Direction to next node*/
		vv_sub(&curpos, &vnodes[i][cnode[i]], &enemyobj[i].transform.pos);

		/*player and enemy i overlap*/
		if (aabb_overlap(pl_aabb, &enemyaabb[i]))
		{
			overlap = 1;
		}

		if (vv_sqrDistance(&enemyobj[i].transform.pos, &vnodes[i][cnode[i]])<600)
		{
			++cnode[i];
			if (vnodes[i][cnode[i]].vy == -1)
				cnode[i] = 0;
		}

		vv_move_towards(&enemyobj[i].transform.pos, &enemyobj[i].transform.pos, &vnodes[i][cnode[i]], 20);
	}
}

inline void enemy_render()
{
	register int i;
	for(i = 0; i < current_active_enemies; ++i)
	{
		render_draw(&enemyobj[i]);
	}
}

inline int enemy_on_player()
{
	return overlap;
}
