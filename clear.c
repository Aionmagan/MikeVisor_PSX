/*
 * clear.c
 *
 *  Created on: Jan 25, 2024
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include <libps.h>
#include "DATA.H"
#include "clear.h"
#include "player.h"
#include "fw.h"

obj_t   clearobj;
aabb_t  clearaa;
aabb_t* playeraa;
VECTOR  clearsca={128, 128, 128};
int     clear_active = 0;
int     clear_check = 0;

void clear_init()
{
	obj_init(&clearobj);
	aabb_init(&clearaa, &clearobj.transform.pos, &clearsca);
	load_model(&clearobj, (long*)CLEAR_DATA);

	playeraa = player_getaabb();
}

void clear_placement(long x, long y, long z)
{
	clearobj.transform.pos.vx = x;
	clearobj.transform.pos.vy = y;
	clearobj.transform.pos.vz = z;

	clear_active = 0;
	clear_check  = 0;
}

void clear_update()
{
	if (clear_active == 0)
		return;

	aabb_update(&clearaa, &clearobj.transform.pos, &clearsca);

	if (aabb_overlap(&clearaa, playeraa))
		clear_check = 1;
}

int clear_checked()
{
	clear_active = 1;

	return clear_check;
}

void clear_render()
{
	if (clear_active)
		render_draw(&clearobj);
}
