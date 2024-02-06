/*
 * player.c
 *
 *  Created on: Nov 26, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */
#include <libps.h>
#include "player.h"
#include "DATA.H"
#include "fw.h"

/*collision data for the player*/
#include "lv0_col.c"
#include "lv1_col.c"
#include "lv2_col.c"
#include "lv3_col.c"
#include "lv4_col.c"
#include "lv5_col.c"
#include "lv6_col.c"
#include "lv7_col.c"
#include "lv8_col.c"
#include "lv9_col.c"

#define PLY_ANIM_AMOUNT 13
#define PLY_MAXSPEED 32
#define PLY_NORSPEED 16

aobj_t      player;
aabb_t      player_aabb;
transform_t cam_target;
transform_t visor_view;
short       camrot = 0;
short       btnpres[4]={0};
int         is_dead = 0;
int         plyr_speed = 32;
long        plyr_height;
VECTOR      plyr_sca = {128, 128, 128};
VECTOR      last_pos;
VECTOR      placement;
VECTOR      cpoints[4];
VECTOR      coffset[4];

static VECTOR* lvl_verts;
static VECTOR* lvl_faces;
static int     lvl_count;

void player_init()
{
	aobj_init(&player);
	aabb_init(&player_aabb, &player.transform.pos, &plyr_sca);
	transform_zero(&cam_target);
	transform_zero(&visor_view);

	render_camera(&player.transform, 0, 0, 0, 0, 0, 0);

	vv_zero(&coffset[0]);
	vv_zero(&coffset[1]);
	vv_zero(&coffset[2]);
	vv_zero(&coffset[3]);

	coffset[0].vx =  32;
	coffset[1].vx = -32;
	coffset[2].vz =  32;
	coffset[3].vz = -32;

	/*IDLE FRAME*/
	dload_model(&player.gsObjectHandler[0],
				&player.transform.gsObjectCoord,
				(long*)CHARI_DATA);

	/*RUN FRAMES*/
	dload_model(&player.gsObjectHandler[1],
				&player.transform.gsObjectCoord,
				(long*)CHARR1_DATA);
	dload_model(&player.gsObjectHandler[2],
				&player.transform.gsObjectCoord,
				(long*)CHARR2_DATA);

	dload_model(&player.gsObjectHandler[3],
				&player.transform.gsObjectCoord,
				(long*)CHARR3_DATA);

	dload_model(&player.gsObjectHandler[4],
				&player.transform.gsObjectCoord,
				(long*)CHARR4_DATA);

	dload_model(&player.gsObjectHandler[5],
				&player.transform.gsObjectCoord,
				(long*)CHARR5_DATA);

	dload_model(&player.gsObjectHandler[6],
				&player.transform.gsObjectCoord,
				(long*)CHARR6_DATA);

	dload_model(&player.gsObjectHandler[7],
				&player.transform.gsObjectCoord,
				(long*)CHARR7_DATA);

	dload_model(&player.gsObjectHandler[8],
				&player.transform.gsObjectCoord,
				(long*)CHARR8_DATA);

	dload_model(&player.gsObjectHandler[9],
				&player.transform.gsObjectCoord,
				(long*)CHARR9_DATA);

	dload_model(&player.gsObjectHandler[10],
				&player.transform.gsObjectCoord,
				(long*)CHARR10_DATA);

	dload_model(&player.gsObjectHandler[11],
				&player.transform.gsObjectCoord,
				(long*)CHARR11_DATA);

	dload_model(&player.gsObjectHandler[12],
				&player.transform.gsObjectCoord,
				(long*)CHARR12_DATA);
}

void player_placement(long x, long y, long z)
{
	player.transform.pos.vx = x;
	player.transform.pos.vy = y;
	player.transform.pos.vz = z;

	cam_target.rot.vy = 0;
	camrot            = 0;
	last_pos          = player.transform.pos;
	is_dead           = 0;

	placement.vx = x;
	placement.vy = y;
	placement.vz = z;

	transform_apply(&player.transform);
}

void player_on_level(short lvl)
{
	switch(lvl)
	{
		case 0:
			lvl_verts = lv0_col_vert;
			lvl_faces = lv0_col_faces;
			lvl_count = LV0_COL_FACE_COUNT;
			break;
		case 1:
			lvl_verts = lv1_col_vert;
			lvl_faces = lv1_col_faces;
			lvl_count = LV1_COL_FACE_COUNT;
			break;
		case 2:
			lvl_verts = lv2_col_vert;
			lvl_faces = lv2_col_faces;
			lvl_count = LV2_COL_FACE_COUNT;
			break;
		case 3:
			lvl_verts = lv3_col_vert;
			lvl_faces = lv3_col_faces;
			lvl_count = LV3_COL_FACE_COUNT;
			break;
		case 4:
			lvl_verts = lv4_col_vert;
			lvl_faces = lv4_col_faces;
			lvl_count = LV4_COL_FACE_COUNT;
			break;
		case 5:
			lvl_verts = lv5_col_vert;
			lvl_faces = lv5_col_faces;
			lvl_count = LV5_COL_FACE_COUNT;
			break;
		case 6:
			lvl_verts = lv6_col_vert;
			lvl_faces = lv6_col_faces;
			lvl_count = LV6_COL_FACE_COUNT;
			break;
		case 7:
			lvl_verts = lv7_col_vert;
			lvl_faces = lv7_col_faces;
			lvl_count = LV7_COL_FACE_COUNT;
			break;
		case 8:
			lvl_verts = lv8_col_vert;
			lvl_faces = lv8_col_faces;
			lvl_count = LV8_COL_FACE_COUNT;
			break;
		case 9:
			lvl_verts = lv9_col_vert;
			lvl_faces = lv9_col_faces;
			lvl_count = LV9_COL_FACE_COUNT;
			break;
		default:break;
	}
}

inline void player_update()
{
	/*fps camera*/
	if (pad_button(PAD_CIRCLE))
	{
		visor_view.pos = player.transform.pos;
		visor_view.pos.vy -= 256;
		visor_view.rot = player.transform.rot;

		if (pad_button(PAD_LEFT))
			player.transform.rot.vy -= 10;
		if (pad_button(PAD_RIGHT))
			player.transform.rot.vy += 10;

		transform_apply(&visor_view);

		render_camera(&visor_view, 0, 0, 5, 0, 0, 0);
		return;
	}

	player.transform.forward = cam_target.forward;
	player.transform.right   = cam_target.right;

	aabb_update(&player_aabb, &player.transform.pos, &plyr_sca);

	if (pad_button(PAD_SQUARE))
	{
		plyr_speed = PLY_MAXSPEED;
	}else{
		plyr_speed = PLY_NORSPEED;
	}

	if (pad_button(PAD_UP))
	{
		transform_local_translate(&player.transform, 0, 0, -plyr_speed);
		player.transform.rot.vy = 0+camrot;
		btnpres[0] = 1;
	}else if (pad_button(PAD_DOWN))
	{
		transform_local_translate(&player.transform, 0, 0, plyr_speed);
		player.transform.rot.vy = 2048+camrot;
		btnpres[1] = 1;
	}else{btnpres[0] = 0; btnpres[1] = 0;}


	if (pad_button(PAD_RIGHT))
	{
		transform_local_translate(&player.transform, -plyr_speed, 0, 0);
		player.transform.rot.vy = 1024+camrot;
		btnpres[2] = 1;

		if (pad_button(PAD_UP))
		{
			player.transform.rot.vy = 512+camrot;
		}else if (pad_button(PAD_DOWN))
		{
			player.transform.rot.vy = 1536+camrot;
		}
	}else if (pad_button(PAD_LEFT))
	{
		transform_local_translate(&player.transform, plyr_speed, 0, 0);
		player.transform.rot.vy = 3072+camrot;
		btnpres[3] = 1;

		if (pad_button(PAD_UP))
		{
			player.transform.rot.vy = -512+camrot;
		}else if (pad_button(PAD_DOWN))
		{
			player.transform.rot.vy = -1536+camrot;
		}
	}else{btnpres[2] = 0; btnpres[3] = 0;}

	/*four point offset for checking collision with the level*/
	vv_add(&cpoints[0], &player.transform.pos, &coffset[0]);
	vv_add(&cpoints[1], &player.transform.pos, &coffset[1]);
	vv_add(&cpoints[2], &player.transform.pos, &coffset[2]);
	vv_add(&cpoints[3], &player.transform.pos, &coffset[3]);

	player.transform.pos.vy += 32;

	/*trash detection of player on level*/
	if (mesh_collision(&player.transform.pos.vy, &player.transform.pos, lvl_verts, lvl_faces, lvl_count) ||
		mesh_collision(&player.transform.pos.vy, &cpoints[0], lvl_verts, lvl_faces, lvl_count) ||
		mesh_collision(&player.transform.pos.vy, &cpoints[1], lvl_verts, lvl_faces, lvl_count) ||
		mesh_collision(&player.transform.pos.vy, &cpoints[2], lvl_verts, lvl_faces, lvl_count) ||
		mesh_collision(&player.transform.pos.vy, &cpoints[3], lvl_verts, lvl_faces, lvl_count))
	{
		//FntPrint("INSIDE MESH\n");
		plyr_height = player.transform.pos.vy;
	}else
	{
		if (player.transform.pos.vy > plyr_height+600)
			is_dead = 1;
	}

	if (pad_button_down(PAD_L1) || pad_button_down(PAD_R2))
	{
		camrot += 1024;
		if (camrot >= ONE)
		{
			cam_target.rot.vy = -1024;
			camrot = 0;
		}
	}
	else if (pad_button_down(PAD_R1) || pad_button_down(PAD_L2))
	{
		camrot -= 1024;
		if (camrot <= -ONE)
		{
			cam_target.rot.vy = 1024;
			camrot = 0;
		}
	}

	/*if moving in any direction then animate depending on speed*/
	if (btnpres[0]||btnpres[1]||btnpres[2]||btnpres[3])
	{
		if (plyr_speed == PLY_NORSPEED)
			aobj_anim(&player, 1, 12, 2);
		if (plyr_speed == PLY_MAXSPEED)
			aobj_anim(&player, 1, 12, 1);
	}else
	{
		player.gsFrame = 0;
	}

	/*used to place enemies and crystals*/
	/*FntPrint("player pos = %d %d %d\n", player.transform.pos.vx,
			                            player.transform.pos.vy,
										player.transform.pos.vz);
	*/
	cam_target.rot.vy = slerp(cam_target.rot.vy, camrot, TOFIXED(819, 1));
	cam_target.pos    = player.transform.pos;

	transform_apply(&cam_target);
	transform_apply(&player.transform);

	render_camera(&cam_target, 0, -1500, 1000, 0, -250, 0);
}

inline void player_render()
{
	render_gdraw(&player.gsObjectHandler[player.gsFrame]);
}

inline int player_dead()
{
	return is_dead;
}

aabb_t* player_getaabb()
{
	return &player_aabb;
}
