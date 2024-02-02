/*
 * aabb.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_AABB_H_
#define FRAMEWORK_AABB_H_

#include <libps.h>

typedef struct
{
	VECTOR  min;
	VECTOR  max;
	int     is_active;
	int     hit;

	VECTOR* owner_pos;
}aabb_t;

void        aabb_init   (aabb_t* a, VECTOR* pos, VECTOR* sca);
inline void aabb_update (aabb_t* a, VECTOR* pos, VECTOR* sca);
inline void aabb_hit    (aabb_t* a, aabb_t* b);
inline int  aabb_overlap(aabb_t* a, aabb_t* b);

/*THIS SHOULD BE IN ANOTHER FILE BUT TOO LAZY*/
int mesh_collision(long* y, VECTOR* point, VECTOR* mesh, VECTOR* faces, long face_count);
#endif /* FRAMEWORK_AABB_H_ */
