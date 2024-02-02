/*
 * render.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "render.h"

#define G_SW (320)
#define G_SH (240)

#define G_OT_LENGTH (12)
#define G_MAX_PACKETS (0X4000*24)// (248000)
#define G_SIZE_PRIM (24)

GsOT      othWorld[2];
GsOT_TAG  otWorld[2][1<<G_OT_LENGTH];
PACKET    out_packet[2][G_MAX_PACKETS];

GsF_LIGHT flights[3];
GsRVIEW2  view;

MATRIX    mlocal;
MATRIX    mlight;

int       context;
u_long    vstime;

void render_init(int proj)
{
	SetVideoMode(MODE_NTSC);
	GsInitGraph(G_SW, G_SH, GsINTER|GsOFSGPU, 1, 0);
	GsDefDispBuff(0, 0, 0, G_SH);

	GsInit3D();

	othWorld[0].length = G_OT_LENGTH;
	othWorld[1].length = G_OT_LENGTH;

	othWorld[0].org    = otWorld[0];
	othWorld[1].org    = otWorld[1];

	GsClearOt(0, 0, &othWorld[0]);
	GsClearOt(0, 0, &othWorld[1]);

	GsSetProjection(proj);
}

void render_light(int flag, int dx, int dy, int dz,
		                    int r,  int g,  int b)
{
	flights[flag].vx = dx;
	flights[flag].vy = dy;
	flights[flag].vz = dz;

	flights[flag].r = r;
	flights[flag].g = g;
	flights[flag].b = b;

	GsSetFlatLight(flag, &flights[flag]);
}

void render_quit()
{
	ResetGraph(3);
}

void render_ambient(short r, short g, short b)
{
	GsSetAmbient(r, g, b);
}

inline void render_camera(transform_t* target, int px, int py, int pz,
		                                 int rx, int ry, int rz)
{
	view.vpx = px;
	view.vpy = py;
	view.vpz = pz;

	view.vrx = rx;
	view.vry = ry;
	view.vrz = rz;

	view.super = &target->gsObjectCoord;
	GsSetRefView2(&view);
}

inline void render_begin()
{
    context = GsGetActiveBuff();
    GsSetWorkBase((PACKET *)out_packet[context]);
    GsClearOt(0, 0, &othWorld[context]);
}

inline void render_end()
{
    DrawSync(0);
    vstime = VSync(-1);
    VSync(0);

    GsSwapDispBuff();
    GsSortClear(0, 0, 0, &othWorld[context]);
    GsDrawOt(&othWorld[context]);
}

inline u_long render_tick()
{
	return vstime;
}

inline void render_draw(obj_t* o)
{
	transform_apply(&o->transform);

	GsGetLs(o->gsObjectHandler.coord2, &mlocal);
	GsSetLsMatrix(&mlocal);
	GsSortObject4(&o->gsObjectHandler, &othWorld[context],  14-G_OT_LENGTH, (u_long*)getScratchAddr(0));
}

inline void render_ldraw(obj_t* o)
{
	transform_apply(&o->transform);

	GsGetLws(o->gsObjectHandler.coord2, &mlight, &mlocal);
	GsSetLightMatrix(&mlight);
	GsSetLsMatrix(&mlocal);
	GsSortObject4(&o->gsObjectHandler, &othWorld[context],  4, (u_long*)getScratchAddr(0));
}

inline void render_dsprite(GsSPRITE* s)
{
	GsSortSprite(s, &othWorld[context], 0);
}

inline void render_gdraw(GsDOBJ2* o)
{
	GsGetLs(o->coord2, &mlocal);
	GsSetLsMatrix(&mlocal);
	GsSortObject4(o, &othWorld[context],  14-G_OT_LENGTH, (u_long*)getScratchAddr(0));
}
