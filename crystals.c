/*
 * crystals.c
 *
 *  Created on: Nov 26, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "crystals.h"
#include "fw.h"
#include "DATA.H"
#include "player.h"

static int current_active_crs = 2;
aobj_t     crsobj        [CRYSTALS_MAX_AMOUNT];
aabb_t     crs_aabb      [CRYSTALS_MAX_AMOUNT];
int        active_values [CRYSTALS_MAX_AMOUNT];
int        current_values[CRYSTALS_MAX_AMOUNT];
int        all_active = 0;
int        cur_active = 0;

aabb_t* plyr_aabb;
VECTOR  crs_sca = {128, 128, 128};

void crystals_init()
{
	int i;
	for(i = 0; i < CRYSTALS_MAX_AMOUNT; ++i)
	{
		aobj_init(&crsobj[i]);
		aabb_init(&crs_aabb[i], &crsobj[i].transform.pos, &crs_sca);

		dload_model(&crsobj[i].gsObjectHandler[0],
				    &crsobj[i].transform.gsObjectCoord,
					(long*)DIADIS_DATA);

		dload_model(&crsobj[i].gsObjectHandler[1],
					&crsobj[i].transform.gsObjectCoord,
					(long*)DIAENA_DATA);
	}

	plyr_aabb = player_getaabb();
}

void crystals_placement(int index, int x, int y, int z, int value)
{
	crsobj[index].transform.pos.vx = x;
	crsobj[index].transform.pos.vy = y;
	crsobj[index].transform.pos.vz = z;
	crsobj[index].gsFrame          = 0;
	active_values[index]           = value;
}

void crystals_set_actives(int i)
{
	current_active_crs = i;
	cur_active = 0;
	all_active = 0;
	for(i = 0; i < current_active_crs; ++i)
					crsobj[i].gsFrame = 0;
}

inline int crystals_all_active()
{
	return all_active;
}

inline void crystals_update()
{
	int i, j;
	for(i = 0; i < current_active_crs; ++i)
	{
		aabb_update(&crs_aabb[i], &crsobj[i].transform.pos, &crs_sca);

		crsobj[i].transform.rot.vy += 16;
		transform_apply(&crsobj[i].transform);

		if (aabb_overlap(plyr_aabb, &crs_aabb[i]))
		{
			if (pad_button_down(PAD_CROSS))
			{
				if (cur_active == active_values[i])
				{
					if (crsobj[i].gsFrame == 0)
					{
						current_values[i] = cur_active++;
						crsobj[i].gsFrame=1;
					}

					/*play pickup sound*/
					audio_sfx_play(1, 48, 127);
				}else
				{
					if (crsobj[i].gsFrame == 1)
						return;

					for(j = 0; j < current_active_crs; ++j)
						crsobj[j].gsFrame = 0;

					/*Play failed sound*/
					/*plays 2 different sounds depending on
					 *if you have already collected crystals or not*/
					if (cur_active <= 0)
						audio_sfx_play(2, 48, 127);
					else
						audio_sfx_play(4, 48, 127);

					cur_active = 0;
				}
			}
		}
	}

	if (cur_active == current_active_crs)
		all_active = 1;

}

inline void crystals_render()
{
	register int i;
	for(i = 0; i < current_active_crs; ++i)
	{
		render_gdraw(&crsobj[i].gsObjectHandler[crsobj[i].gsFrame]);
	}
}

