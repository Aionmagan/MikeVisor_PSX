/*
 * obj.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_OBJ_H_
#define FRAMEWORK_OBJ_H_

#include <libps.h>

static u_long pmode_tex;

typedef struct
{
	/*model space*/
	SVECTOR up;
	SVECTOR right;
	SVECTOR forward;

	/*world space*/
	VECTOR  pos;
	VECTOR  sca;
	SVECTOR rot;

	GsCOORDINATE2 gsObjectCoord;
}transform_t;

/*for static objects*/
typedef struct
{
	transform_t transform;
	GsDOBJ2       gsObjectHandler;
	//GsCOORDINATE2 gsObjectCoord;
}obj_t;

/*for animated objects*/
typedef struct
{
	transform_t transform;
	GsDOBJ2     gsObjectHandler[13]; //should be changed to a pointer later
	short       gsFrame;
	u_long      gsCounter;
}aobj_t;

void obj_init    (obj_t* o);
void aobj_init   (aobj_t* a);
void load_texture(long addr);
void load_model  (obj_t* o, unsigned long* addr);
void load_sprite (GsSPRITE* sprite, unsigned long* addr);
/*direct loading*/
void dload_model (GsDOBJ2* handle, GsCOORDINATE2* coord, unsigned long* addr);
inline void aobj_anim(aobj_t* a, u_short start_frame, u_short frame_limit, u_short slowness);

void        transform_zero                (transform_t* t);
inline void transform_local_translate     (transform_t* t, int x, int y, int z);
/*used by render.h internally*/
inline void transform_update_local        (transform_t* t);
inline void transform_apply               (transform_t* t);
/*used by render.h internally*/

#endif /* FRAMEWORK_OBJ_H_ */
