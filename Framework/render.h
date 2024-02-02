/*
 * render.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_RENDER_H_
#define FRAMEWORK_RENDER_H_

#include "obj.h"

#define GLIGHT0 0
#define GLIGHT1 1
#define GLIGHT2 2

void render_init(int proj);
void render_quit();
void render_ambient(short r, short g, short b);
void render_light(int flag, int dx, int dy, int dz,
		                    int r,  int g,  int b);

inline void render_camera(transform_t* target, int px, int py, int pz,
		                                 int rx, int ry, int rz);
inline void   render_begin();
inline void   render_end();
inline u_long render_tick();
inline void   render_draw(obj_t* o);
inline void   render_ldraw(obj_t* o);
inline void   render_dsprite(GsSPRITE* s);

inline void   render_gdraw(GsDOBJ2* o);
#endif /* FRAMEWORK_RENDER_H_ */
