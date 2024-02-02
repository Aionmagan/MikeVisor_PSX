/*
 * audio.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Noel Rojas Oliveras
 *
 *  if you are reading this, check out "http://netyaroze.com/discord"
 */
#include "audio.h"
#include <libps.h>

short vab = 0;
short SEQA[SEQ_AMOUNT];
short seq_count = 0;

void audio_init(long* seqarray, int seqamount, long* vhaddr, long* vbaddr)
{
	int i;
	vab = SsVabTransfer((u_char*)vhaddr, (u_char*)vbaddr, -1, 1);

	if (vab < 0)
		return;

	for(i = 0; i < seqamount; ++i)
		SEQA[i] = SsSeqOpen((long*)seqarray[i], vab);

	seq_count = seqamount;
	SsSetMVol(MAIN_VOL, MAIN_VOL);
}

void audio_quit()
{
	int i;
	for(i = 0; i < seq_count; ++i)
		SsSeqStop(SEQA[i]);

	VSync(0);
	VSync(0);

	for(i = 0; i < seq_count; ++i)
		SsSeqClose(SEQA[i]);
	SsVabClose(vab);
}

void audio_sfx_play(short sfxindex, short pitch, short vol)
{
	SsUtKeyOn(vab, sfxindex, 0, pitch, 0, vol, vol);
}

void audio_play(short seqindex, short counts)
{
	//SsUtKeyOn(vab, 0, 0, 48, 0, 127, 127);
	//return;
	//SsSetMVol(MAIN_VOL, MAIN_VOL);
	SsSeqSetVol(SEQA[seqindex], SEQ_VOL, SEQ_VOL);

	if (counts <= -1)
		SsSeqPlay(SEQA[seqindex], SSPLAY_PLAY, SSPLAY_INFINITY);
	else
		SsSeqPlay(SEQA[seqindex], SSPLAY_PLAY, counts);
}

void audio_stop(short seqindex)
{
	SsSeqStop(SEQA[seqindex]);
	VSync(0);
	VSync(0);
}
