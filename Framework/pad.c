/*
 * pad.c
 *
 *  Created on: Oct 20, 2023
 *      Author: Noel Rojas Oliveras
 */

#include "pad.h"
#include <libps.h>

volatile u_char* buff[8];
u_long           cur_state;
u_long           old_state;
u_long           is_down;


void pad_init()
{
	GetPadBuf(&buff[0], &buff[1]);
	cur_state = 0;
	old_state = 0;
}

void pad_read()
{
	/*Check if buttons were down last time*/
	is_down = cur_state & (cur_state ^ old_state);

	old_state = cur_state;
	cur_state = ~((buff[0][3] <<  0) |
				  (buff[0][2] <<  8));
}

int pad_button(int flag)
{
	return flag & cur_state;
}

int pad_button_down(int flag)
{
	return is_down & flag;
}


