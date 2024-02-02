/*
 * aabb.c
 *
 *  Created on: Nov 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#include "aabb.h"
#include "vmath.h"

void aabb_init(aabb_t* a, VECTOR* pos, VECTOR* sca)
{
	vv_sub(&a->min, pos, sca);
	vv_add(&a->max, pos, sca);
	a->is_active = 1;
	a->hit = 0;
}

inline void aabb_update(aabb_t* a, VECTOR* pos, VECTOR* sca)
{
	vv_sub(&a->min, pos, sca);
	vv_add(&a->max, pos, sca);

	a->hit = 0;
}

inline void aabb_hit(aabb_t* a, aabb_t* b)
{
	if (aabb_overlap(a, b))
	{
		a->hit = 1;
		b->hit = 1;
	}
}

inline int aabb_overlap(aabb_t* a, aabb_t* b)
{
	if (a->is_active == 0 || b->is_active == 0)
		return 0;

	return(a->max.vx > b->min.vx &&
    	   a->min.vx < b->max.vx &&
    	   a->max.vy > b->min.vy &&
    	   a->min.vy < b->max.vy &&
    	   a->max.vz > b->min.vz &&
    	   a->min.vz < b->max.vz);
}

#if 1
/*THIS SHOULD BE IN ANOTHER FILE BUT TOO LAZY*/
int ptInTriangle(VECTOR p, VECTOR p0, VECTOR p1, VECTOR p2)
{
	/*this fixedpoint version was removed because vertex data isn't fixed point it's just rounded*/
#if 0
    long A = (-FIXEDMUL(p1.vz, p2.vx) +
    		   FIXEDMUL(p0.vz, (-p1.vx + p2.vx)) +
			   FIXEDMUL(p0.vx, (p1.vz - p2.vz)) +
			   FIXEDMUL(p1.vx, p2.vz)) * 5120;

    long sign = A < 0 ? -1 : 1;

    long s =(FIXEDMUL(p0.vz, p2.vx) -
    		 FIXEDMUL(p0.vx, p2.vz) +
			 FIXEDMUL((p2.vz - p0.vz), p.vx) +
			 FIXEDMUL((p0.vx - p2.vx), p.vz))* sign;

    long t = (FIXEDMUL(p0.vx, p1.vz) -
    		  FIXEDMUL(p0.vz, p1.vx) +
			  FIXEDMUL((p0.vz - p1.vz), p.vx) +
			  FIXEDMUL((p1.vx - p0.vx), p.vz))* sign;

    return (s > 0 && t > 0 && (s + t) < (ONE) * A * sign);

#else

    long A = (-p1.vz * p2.vx + p0.vz * (-p1.vx + p2.vx) + p0.vx * (p1.vz - p2.vz) + p1.vx * p2.vz)>>1;
    long sign = A < 0 ? -1 : 1;
    long s = (p0.vz * p2.vx - p0.vx * p2.vz + (p2.vz - p0.vz) * p.vx + (p0.vx - p2.vx) * p.vz) * sign;
    long t = (p0.vx * p1.vz - p0.vz * p1.vx + (p0.vz - p1.vz) * p.vx + (p1.vx - p0.vx) * p.vz) * sign;

    return (s > 0 && t > 0 && (s + t) < 2 * A * sign);
#endif
}

int mesh_collision(long* y, VECTOR* point, VECTOR* mesh, VECTOR* faces, long face_count)
{
	/*outdated and none working*/
#if 0
	  int i, j, c = 0;
	  int verty, vertx;
	  for (i = 0, j = face_count-1; i < face_count; j = i++)
	  {

		vertx =  mesh[faces[i].vx].vx;
		verty =  mesh[faces[i].vx].vz;

	    if ( ((verty>point->vy) != (verty>point->vy)) &&
		      (point->vx < (vertx-vertx) * (point->vx-verty) /
			  (verty-verty) + vertx) )
	       c = !c;

	    if (c)
	    {
	    	*y = mesh[faces[i].vx].vy;
	    	return 1;
	    }
	  }
	  return 0;
#else
    static int A;
	static int i;

	for(i = 0; i < face_count; ++i)
	{

		A = ptInTriangle(*point,
		    mesh[faces[i].vx],
		    mesh[faces[i].vy],
		    mesh[faces[i].vz]);

		if (A)
		{
			*y = mesh[faces[i].vx].vy;
			return 1;
		}
	}
	return 0;
#endif
}
#endif
