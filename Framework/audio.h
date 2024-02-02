/*
 * audio.h
 *
 *  Created on: Jan 23, 2024
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */

#ifndef FRAMEWORK_AUDIO_H_
#define FRAMEWORK_AUDIO_H_

#define SEQ_AMOUNT 10
#define SEQ_VOL 115
#define MAIN_VOL 127

/* seqarray must be an array with all the pointers to seq address
 * seqamount is the length of the array
 * vhaddr is a needed empty address
 * vbaddr is a needed empty address*/
void audio_init(long* seqarray, int seqamount, long* vhaddr, long* vbaddr);
void audio_quit();

/* seqindex is just an index (seqarray is processed in order of array)
 * counts is repition amount (if send -1 then its infinite) */
void audio_sfx_play(short sfxindex, short pitch, short vol);
void audio_play(short seqindex, short counts);
void audio_stop(short seqindex);

#endif /* FRAMEWORK_AUDIO_H_ */
