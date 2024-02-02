/*
 * fmath.h
 *
 *  Created on: Nov 15, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_FMATH_H_
#define FRAMEWORK_FMATH_H_

#include <libps.h>

#define FIXED_POINT_SIZE 12

#define FIXEDMUL(a,b) ((a)*(b) >> FIXED_POINT_SIZE)
#define FIXEDDIV(a,b) (((a) << FIXED_POINT_SIZE)/(b))
#define TOFIXED(n, bits) ((n)<<(bits))
#define FROMFIXED(n, bits) ((n)>>(bits))
#define FIXEDABS(a) (a > 0 ? a : (0-a))



/*long lerp*/
static long llerp(long f1, long f2, long l)
{
	return f1 + FIXEDMUL(l ,(f2 - f1));
}

/*short lerp*/
static short slerp(short f1, short f2, short l)
{
	return f1 + FIXEDMUL(l ,(f2 - f1));
}

static long move_towards(long f1, long f2, long d)
{
	register long i;
	i = (f2-f1);
	//return f1 + FIXEDMUL((i >= 0 ? 1 : -1), d);
	return f1 + ((i >= 0 ? 1 : -1)* d);
}

#endif /* FRAMEWORK_FMATH_H_ */
