/*
 * pad.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_PAD_H_
#define FRAMEWORK_PAD_H_

#define PAD_UP     	 (1<<12)
#define PAD_DOWN   	 (1<<14)
#define PAD_LEFT   	 (1<<15)
#define PAD_RIGHT  	 (1<<13)
#define PAD_TRIANGLE (1<<4)
#define PAD_CROSS    (1<<6)
#define PAD_SQUARE   (1<<7)
#define PAD_CIRCLE   (1<<5)
#define PAD_START  	 (1<<11)
#define PAD_SELECT   (1<<8)
#define PAD_L1       (1<<2)
#define PAD_L2       (1<<0)
#define PAD_R1       (1<<3)
#define PAD_R2       (1<<1)

void pad_init();
void pad_read();
int  pad_button(int flag);
int  pad_button_down(int flag);

#endif /* FRAMEWORK_PAD_H_ */
