/*
 * obj.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "obj.h"
#include "render.h"
#include "fmath.h"
#include <libps.h>

//MATRIX olocal;
MATRIX  otransform;

SVECTOR wfo={0, 0, ONE};
SVECTOR wri={ONE, 0, 0};
SVECTOR wup={0, ONE, 0};

void obj_init(obj_t* o)
{
	memset((void *)(o), 0, sizeof(obj_t));

	transform_zero(&o->transform);

	GsInitCoordinate2(WORLD, &o->transform.gsObjectCoord);
	o->transform.gsObjectCoord.coord = GsIDMATRIX;
	o->transform.gsObjectCoord.flg = 0;
}

void aobj_init(aobj_t* a)
{
	memset((void *)(a), 0, sizeof(aobj_t));

	transform_zero(&a->transform);
	a->gsFrame = 0;
	a->gsCounter = 0;
	GsInitCoordinate2(WORLD, &a->transform.gsObjectCoord);
	a->transform.gsObjectCoord.coord = GsIDMATRIX;
	a->transform.gsObjectCoord.flg = 0;
}

void load_texture(long addr)
{
	RECT rect;
	GsIMAGE tim1;
	u_long* tim = (u_long*)addr; tim++;
	//GsGetTimInfo((u_long*)(addr+4), &tim1);
	GsGetTimInfo(tim, &tim1);

	rect.x=tim1.px;
	rect.y=tim1.py;
	rect.w=tim1.pw;
	rect.h=tim1.ph;
	LoadImage(&rect, tim1.pixel);

	if ((tim1.pmode>>3)&0x01)
	{
		rect.x=tim1.cx;
		rect.y=tim1.cy;
		rect.w=tim1.cw;
		rect.h=tim1.ch;

		LoadImage(&rect, tim1.clut);
	}

	DrawSync(0);
}

void load_model(obj_t* o, unsigned long* addr)
{
	addr++;
	//o->gsObjectHandler.attribute |= 1<<3;
	o->gsObjectHandler.attribute |= 1<<6;
	//thePlayer->gsObjectHandler.attribute |= 1<<31;
	GsMapModelingData(addr);
	GsInitCoordinate2(WORLD, &o->transform.gsObjectCoord);
	o->gsObjectHandler.coord2 = &o->transform.gsObjectCoord;

	//lModelAddress+=2;
	addr++; addr++;

	GsLinkObject4(addr, &o->gsObjectHandler, 0);
}

void load_sprite (GsSPRITE* sprite, unsigned long* addr, int clut_flag)
{
	GsIMAGE img;
	RECT rect = {0};
	u_long* tim = (u_long*)addr; tim++;

	//img.pmode = 0;
	GsGetTimInfo(tim, &img);
	setRECT(&rect, img.px, img.py, img.pw, img.ph);
	LoadImage(&rect, img.pixel);

	setRECT(&rect, img.cx, img.cy, img.cw, img.ch);
	LoadImage(&rect, img.clut);

	//testSprite.attribute |= (1<<30);
	//testSprite.attribute |= (1<<29);
	sprite->attribute = 0;
	sprite->attribute |= (clut_flag<<24);
	sprite->w = img.pw*4;
	sprite->h = img.ph;
	sprite->tpage = GetTPage(0, 0, img.px, img.py);

	sprite->x = 0;
	sprite->y = 0;
	sprite->u = 0;
	sprite->v = 0;

	sprite->r =
	sprite->b =
	sprite->g = 80;

	sprite->cx = img.cx; sprite->cy = img.cy;
	sprite->mx = sprite->w>>1;
	sprite->my = sprite->h>>1;

	sprite->scalex = ONE + 2048;
	sprite->scaley = ONE + 2048;
	sprite->rotate = 0;
}

void dload_model(GsDOBJ2* handle, GsCOORDINATE2* coord, unsigned long* addr)
{
	addr++;
	//o->gsObjectHandler.attribute |= 1<<3;
	handle->attribute |= 1<<6;
	//thePlayer->gsObjectHandler.attribute |= 1<<31;
	GsMapModelingData(addr);
	GsInitCoordinate2(WORLD, coord);
	handle->coord2 = coord;

	//lModelAddress+=2;
	addr++; addr++;

	GsLinkObject4(addr, handle, 0);
}

inline void aobj_anim(aobj_t* a, u_short start_frame, u_short frame_limit, u_short slowness)
{
	if (a->gsCounter < render_tick())
	{
		a->gsFrame++;
		if (a->gsFrame > frame_limit) a->gsFrame = start_frame;
		a->gsCounter = render_tick() + slowness;
	}
}

void transform_zero(transform_t* t)
{
	/*Local space*/
	t->forward = wfo;
	t->right   = wri;
	t->up      = wup;
	/*Local space*/

	t->pos.vx = 0;
	t->pos.vy = 0;
	t->pos.vz = 0;

	t->sca.vx = ONE;
	t->sca.vy = ONE;
	t->sca.vz = ONE;

	t->rot.vx = 0;
	t->rot.vy = 0;
	t->rot.vz = 0;

	GsInitCoordinate2(WORLD, &t->gsObjectCoord);
	t->gsObjectCoord.coord = GsIDMATRIX;
	t->gsObjectCoord.flg = 0;
}


inline void transform_local_translate(transform_t* t, int x, int y, int z)
{
	//register int xx = x*x;
	//register int yy = y*y;
	//register int zz = z*z;
	if (FIXEDABS(x))//(xx > 0)
	{
	t->pos.vx += (t->right.vx * x)/ONE;
	t->pos.vy += (t->right.vy * x)/ONE;
	t->pos.vz += (t->right.vz * x)/ONE;
	}

	if (FIXEDABS(y))
	{
	t->pos.vx += (t->up.vx * y)/ONE;
	t->pos.vy += (t->up.vy * y)/ONE;
	t->pos.vz += (t->up.vz * y)/ONE;
	}

	if (FIXEDABS(z))
	{
	t->pos.vx += (t->forward.vx * z)/ONE;
	t->pos.vy += (t->forward.vy * z)/ONE;
	t->pos.vz += (t->forward.vz * z)/ONE;
	}
}

inline void transform_update_local(transform_t* t)
{
	RotMatrix(&t->rot, &otransform);

	ApplyMatrixSV(&otransform, &wri, &t->right);
	ApplyMatrixSV(&otransform, &wup, &t->up);
	ApplyMatrixSV(&otransform, &wfo, &t->forward);
}

inline void transform_apply(transform_t* t)
{
	/*matrix identity*/
	//t->gsObjectCoord.coord.m[0][0]=ONE;
	//t->gsObjectCoord.coord.m[1][1]=ONE;
	//t->gsObjectCoord.coord.m[2][2]=ONE;

	//t->gsObjectCoord.coord.m[0][1]=0;
	//t->gsObjectCoord.coord.m[0][2]=0;
	//t->gsObjectCoord.coord.m[1][0]=0;
	//t->gsObjectCoord.coord.m[1][2]=0;
	//t->gsObjectCoord.coord.m[2][0]=0;
	//t->gsObjectCoord.coord.m[2][1]=0;
	t->gsObjectCoord.coord = GsIDMATRIX;

	t->rot.vx = t->rot.vx%ONE;
	t->rot.vy = t->rot.vy%ONE;
	t->rot.vz = t->rot.vz%ONE;

	ScaleMatrix(&otransform, &t->sca);
	RotMatrix(&t->rot, &otransform);

	transform_update_local(t);

	MulMatrix0(&t->gsObjectCoord.coord, &otransform, &t->gsObjectCoord.coord);

	t->gsObjectCoord.coord.t[0] = t->pos.vx;
	t->gsObjectCoord.coord.t[1] = t->pos.vy;
	t->gsObjectCoord.coord.t[2] = t->pos.vz;

	t->gsObjectCoord.flg = 0;
}
