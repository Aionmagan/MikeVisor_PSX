/*
 * vmath.h
 *
 *  Created on: Nov 21, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_VMATH_H_
#define FRAMEWORK_VMATH_H_

#include "fmath.h"

/*
 *---------------------------------------------------------------------------------------
 *VECTORS from libps.h
 *---------------------------------------------------------------------------------------
 */
static void vv_one(VECTOR* v)
{
	v->vx = ONE;
	v->vx = ONE;
	v->vx = ONE;
}

static void vv_zero(VECTOR* v)
{
	v->vx = 0;
	v->vx = 0;
	v->vx = 0;
}

static void vv_neg(VECTOR* v)
{
	v->vx = -v->vx;
	v->vx = -v->vy;
	v->vx = -v->vz;
}

static void vv_sub(VECTOR* out, VECTOR* v1, VECTOR*v2)
{
#if 1
	asm volatile
	(
		"sub %0, %3, %6  \n\t"
		"sub %1, %4, %7  \n\t"
		"sub %2, %5, %8  \n\t"
		: "=r" (out->vx), "=r" (out->vy), "=r" (out->vz)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz)
		//: "$1", "$2", "$3", "$5", "%6", "%7", "%9", "%10", "$11"
	);
#else
	out->vx = v1->vx - v2->vx;
	out->vy = v1->vy - v2->vy;
	out->vz = v1->vz - v2->vz;
#endif
}

static void vv_add(VECTOR* out, VECTOR* v1, VECTOR*v2)
{
#if 1
	asm volatile
	(
		"add %0, %3, %6  \n\t"
		"add %1, %4, %7  \n\t"
		"add %2, %5, %8  \n\t"
		: "=r" (out->vx), "=r" (out->vy), "=r" (out->vz)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz)
		//: "$1", "$2", "$3", "$5", "%6", "%7", "%9", "%10", "$11"
	);
#else
	out->vx = v1->vx + v2->vx;
	out->vy = v1->vy + v2->vy;
	out->vz = v1->vz + v2->vz;
#endif
}

static void vlerp(VECTOR* out, VECTOR* v1, VECTOR* v2, long l)
{
	out->vx = v1->vx + FIXEDMUL(l,(v2->vx - v1->vx));
	out->vy = v1->vy + FIXEDMUL(l,(v2->vy - v1->vy));
	out->vz = v1->vz + FIXEDMUL(l,(v2->vz - v1->vz));
}

static void vvf_mul(VECTOR* out, VECTOR* v, long l)
{
	out->vx = FIXEDMUL(v->vx, l);
	out->vy = FIXEDMUL(v->vy, l);
	out->vz = FIXEDMUL(v->vx, l);
}

static long vv_sqrDistance(VECTOR* v1, VECTOR* v2)
{
#if 1
	register long r;
	asm volatile
	(
		"sub $5, %1, %4 \n\t"
		"sub $6, %2, %5 \n\t"
		"sub $7, %3, %6 \n\t"
		"mult $5, $5 \n\t"
		"mflo $5     \n\t"
		"mult $6, $6 \n\t"
		"mflo $6     \n\t"
		"mult $7, $7 \n\t"
		"mflo $7     \n\t"
		"add $5, $6, $5 \n\t"
		"add %0, $5, $7 \n\t"
		: "=r"(r)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz)
	);
	return r;
#else
	register long x = v1->vx - v2->vx;
	register long y = v1->vy - v2->vy;
	register long z = v1->vz - v2->vz;
	return ((x*x) + (y*y) + (z*z));
#endif
}

static void vv_move_towards(VECTOR* out, VECTOR* v1, VECTOR* v2, long d)
{
#if 1
	asm volatile
	(
		"addi $0,   $0,  0    \n\t"//zero
		"subu $7,   %6,  %3   \n\t"
		"subu $8,   %7,  %4   \n\t"
		"subu $9,   %8,  %5   \n\t"
		"addu $13,  $0,  %9   \n\t"
		"bgez $7,  .L1        \n\t"
		"subu $13,  $0,  $13  \n\t"
		".L1:                 \n\t"
		"addu $14,  $0,  %9   \n\t"
		"bgez $8,  .L2        \n\t"
		"subu $14,  $0,  $14  \n\t"
		".L2:                 \n\t"
		"addu $15,  $0,  %9   \n\t"
		"bgez $9,  .L3        \n\t"
		"subu $15,  $0,  $15  \n\t"
		".L3:                 \n\t"
		"addu %0,   %3,  $13  \n\t"
		"addu %1,   %4,  $14  \n\t"
		"addu %2,   %5,  $15  \n\t"
		: "=r" (out->vx), "=r" (out->vy), "=r" (out->vz)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz), "r" (d)
		: "$0", "$6", "$7", "$8", "$13", "$14", "$15"
	);
#else
	register long x;
	register long y;
	register long z;

	x = (v2->vx - v1->vx);
	y = (v2->vy - v1->vy);
	z = (v2->vz - v1->vz);

	/*removed multiplication*/
	out->vx = v1->vx + ((x >= 0 ? d+d : 0) - d);
	out->vy = v1->vy + ((y >= 0 ? d+d : 0) - d);
	out->vz = v1->vz + ((z >= 0 ? d+d : 0) - d);
	/*
	out->vx = v1->vx + ((x >= 0 ? 1 : -1) * d);
	out->vy = v1->vy + ((y >= 0 ? 1 : -1) * d);
	out->vz = v1->vz + ((z >= 0 ? 1 : -1) * d);
	*/
#endif
}
/*
 *---------------------------------------------------------------------------------------
 *VECTORS from libps.h
 *---------------------------------------------------------------------------------------
 */


/*
 *---------------------------------------------------------------------------------------
 *SHORT VECTORS from libps.h
 *---------------------------------------------------------------------------------------
 */
static void sv_one(SVECTOR* v)
{
	v->vx = ONE;
	v->vx = ONE;
	v->vx = ONE;
}

static void sv_zero(SVECTOR* v)
{
	v->vx = 0;
	v->vx = 0;
	v->vx = 0;
}

static void sv_neg(SVECTOR* v)
{
	v->vx = -v->vx;
	v->vx = -v->vy;
	v->vx = -v->vz;
}

static void sv_sub(SVECTOR* out, SVECTOR* v1, SVECTOR*v2)
{
#if 1
	asm volatile
	(
		"sub %0, %3, %6  \n\t"
		"sub %1, %4, %7  \n\t"
		"sub %2, %5, %8  \n\t"
		: "=r" (out->vx), "=r" (out->vy), "=r" (out->vz)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz)
		//: "$1", "$2", "$3", "$5", "%6", "%7", "%9", "%10", "$11"
	);
#else
	out->vx = v1->vx - v2->vx;
	out->vy = v1->vy - v2->vy;
	out->vz = v1->vz - v2->vz;
#endif
}

static void sv_add(SVECTOR* out, SVECTOR* v1, SVECTOR*v2)
{
#if 1
	asm volatile
	(
		"add %0, %3, %6  \n\t"
		"add %1, %4, %7  \n\t"
		"add %2, %5, %8  \n\t"
		: "=r" (out->vx), "=r" (out->vy), "=r" (out->vz)
		: "r" (v1->vx), "r" (v1->vy), "r" (v1->vz),"r" (v2->vx), "r" (v2->vy), "r" (v2->vz)
		//: "$1", "$2", "$3", "$5", "%6", "%7", "%9", "%10", "$11"
	);
#else
	out->vx = v1->vx + v2->vx;
	out->vy = v1->vy + v2->vy;
	out->vz = v1->vz + v2->vz;
#endif
}

static void svlerp(SVECTOR* out, SVECTOR* v1, SVECTOR* v2, long l)
{
	out->vx = v1->vx + FIXEDMUL(l,(v2->vx - v1->vx));
	out->vy = v1->vy + FIXEDMUL(l,(v2->vy - v1->vy));
	out->vz = v1->vz + FIXEDMUL(l,(v2->vz - v1->vz));
}

static void svf_mul(SVECTOR* out, SVECTOR* v, long l)
{
	out->vx = FIXEDMUL(v->vx, l);
	out->vy = FIXEDMUL(v->vy, l);
	out->vz = FIXEDMUL(v->vz, l);
}
/*
 *---------------------------------------------------------------------------------------
 *SHORT VECTORS from libps.h
 *---------------------------------------------------------------------------------------
 */
#endif /* FRAMEWORK_VMATH_H_ */
