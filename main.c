#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fw.h"
#include <libps.h>
#include "DATA.H"

#include "player.h"
#include "enemy.h"
#include "crystals.h"
#include "clear.h"

GsSPRITE credits;

void credit_screen()
{
	long timer = render_tick()+300;
	while(1)
	{
		if (timer < render_tick())
			break;

		render_begin();
			render_dsprite(&credits);
		render_end();
	}
}

void intro_screen()
{
	GsSPRITE logo;
	short istimer = 0;
	short stoptimer = 0;
	short move = 0;
	load_sprite(&logo, (long*)NY_TITLE_DATA);

	logo.scalex = ONE>>1;
	logo.scaley = ONE>>1;

	logo.r = 0;
	logo.g = 0;
	logo.b = 0;

	while(1)
	{
		if(logo.r > 80 && move == 0)
		{
			logo.scalex = ONE+1024;
			logo.scaley = ONE+128;
			logo.rotate = 0;

			if (stoptimer < render_tick())
			{
				move = 1;
				logo.scalex =
				logo.scaley = ONE-2048;
			}
		}else
		{
			logo.rotate += ONE*2048;
			logo.scalex = logo.scaley += move > 0 ? -32 : 32;

			if (logo.scalex <= 0)
				logo.scalex = logo.scaley = 0;

			stoptimer = render_tick() + 200;

			if (istimer < render_tick())
			{
				logo.r =
				logo.g =
				logo.b += move > 0 ? -3 : 3;
				istimer = render_tick();
			}
		}

		if (move && logo.r <= 0) break;

		render_begin();
		render_dsprite(&logo);
		render_end();
	}
}

void load_level(obj_t* o, int i)
{
	switch(i)
	{
	case 0 :
		load_model(o, (long*)LV0_DATA);
		clear_placement(0, 0, 0);
		crystals_placement(0, 620, 0, 624, 3);
		crystals_placement(1, 620, 0,-608, 2);
		crystals_placement(2,-640, 0,-608, 1);
		crystals_placement(3,-640, 0, 624, 0);
		crystals_set_actives(4);
		enemy_set_actives(0);
		player_placement(3, 0, 3);
		break;
	case 1 :
		load_model(o, (long*)LV1_DATA);
		clear_placement(590, 0, 1580);
		crystals_placement(0, -500, 0, -1870, 0);
		crystals_placement(1, -500, 0,  1580, 1);
		crystals_set_actives(2);
		enemy_set_node(0, 0, 0, 0, -1600);
		enemy_set_node(0, 1, 0, 0,  1600);
		enemy_placement(0, 0, 0, 0, 1600);
		enemy_set_actives(1);
		player_placement(590, 0, 1580);
		break;
	case 2 :
		load_model(o, (long*)LV2_DATA);
		clear_placement(-1700, 0, 750);
		crystals_placement(0,  1022, 0, -444, 5);
		crystals_placement(1,  1022, 0, 1840, 4);
		crystals_placement(2,   -10, 0, 1840, 3);
		crystals_placement(3, -1770, 0, 1840, 2);
		crystals_placement(4, -1770, 0, -444, 1);
		crystals_placement(5,   -10, 0, -444, 0);
		crystals_set_actives(6);
		enemy_set_node(0, 0,  1022, 0, -444);
		enemy_set_node(0, 1,  1022, 0, 1840);
		enemy_set_node(1, 0,   -10, 0, 1840);
		enemy_set_node(1, 1, -1770, 0, 1840);
		enemy_set_node(1, 2, -1770, 0, -444);
		enemy_set_node(1, 3,   -10, 0, -444);
		enemy_placement(0, 0, 1022, 0, -444);
		enemy_placement(1, 0,  -10, 0, -444);
		enemy_set_actives(2);
		player_placement(590, 0, 1580);
		break;
	case 3 :
		load_model(o, (long*)LV3_DATA);
		clear_placement(0, 0, 0);
		crystals_placement(0,     0, 0, -1750, 0);
		crystals_placement(1,  1750, 0, -1750, 1);
		crystals_placement(2,  1750, 0,    50, 2);
		crystals_placement(3, -1800, 0,    50, 3);
		crystals_placement(4, -1800, 0,  1800, 4);
		crystals_placement(5,     0, 0,  1800, 5);
		crystals_set_actives(6);
		enemy_set_node(0, 0, -1800, 0,  1800);
		enemy_set_node(0, 1,     0, 0,  1800);
		enemy_set_node(0, 2,     0, 0, -1750);
		enemy_set_node(0, 3,  1750, 0, -1750);
		enemy_set_node(0, 4,  1750, 0,    50);
		enemy_set_node(0, 5, -1800, 0,    50);
		enemy_set_node(1, 0, -1800, 0,  1800);
		enemy_set_node(1, 1,     0, 0,  1800);
		enemy_set_node(1, 2,     0, 0, -1750);
		enemy_set_node(1, 3,  1750, 0, -1750);
		enemy_set_node(1, 4,  1750, 0,    50);
		enemy_set_node(1, 5, -1800, 0,    50);
		enemy_set_node(2, 0, -1800, 0,  1800);
		enemy_set_node(2, 1,     0, 0,  1800);
		enemy_set_node(2, 2,     0, 0, -1750);
		enemy_set_node(2, 3,  1750, 0, -1750);
		enemy_set_node(2, 4,  1750, 0,    50);
		enemy_set_node(2, 5, -1800, 0,    50);
		enemy_placement(0, 0, -1800, 0,  1800);
		enemy_placement(1, 2,     0, 0, -1750);
		enemy_placement(2, 4,  1750, 0,    50);
		enemy_set_actives(3);
		player_placement(414, 0, 1300);
		break;
	case 4 :
		load_model(o, (long*)LV4_DATA);
		clear_placement(0, 0, 0);
		crystals_placement(0,  1800, 0,    50, 0);
		crystals_placement(1,  1800, 0, -1750, 1);
		crystals_placement(2, -1800, 0, -1750, 2);
		crystals_placement(3, -1800, 0,  1750, 3);
		crystals_placement(4,  1800, 0,  1750, 4);
		crystals_set_actives(5);
		enemy_set_node(0, 0,  1800, 0, -1750);
		enemy_set_node(0, 1, -1800, 0, -1750);
		enemy_set_node(0, 2, -1800, 0,  1750);
		enemy_set_node(0, 3,  1800, 0,  1750);
		enemy_set_node(1, 0,  1800, 0, -1750);
		enemy_set_node(1, 1, -1800, 0, -1750);
		enemy_set_node(1, 2, -1800, 0,  1750);
		enemy_set_node(1, 3,  1800, 0,  1750);
		enemy_set_node(2, 0,  1800, 0, -1750);
		enemy_set_node(2, 1, -1800, 0, -1750);
		enemy_set_node(2, 2, -1800, 0,  1750);
		enemy_set_node(2, 3,  1800, 0,  1750);
		enemy_set_node(3, 0,  1800, 0, -1750);
		enemy_set_node(3, 1, -1800, 0, -1750);
		enemy_set_node(3, 2, -1800, 0,  1750);
		enemy_set_node(3, 3,  1800, 0,  1750);
		enemy_placement(0, 0,  1800, 0, -1750);
		enemy_placement(1, 1, -1800, 0, -1750);
		enemy_placement(2, 2, -1800, 0,  1750);
		enemy_placement(3, 3,  1800, 0,  1750);
		enemy_set_actives(4);
		player_placement(-80, 0, 20);
		break;
	case 5 :
		load_model(o, (long*)LV5_DATA);
		clear_placement(500, 0, -700);
		crystals_placement(0,  500,    0,  1550, 0);
		crystals_placement(1, -500, -154,  -470, 1);
		crystals_placement(2,   20,    0, -1500, 2);
		crystals_set_actives(3);
		enemy_set_node(0,  0, -520, -154,  650);
		enemy_set_node(0,  1, -520, -154, -500);
		enemy_set_node(1,  0,  520,    0, 1550);
		enemy_set_node(1,  1,  500,    0,  100);
		enemy_placement(0, 0, -530, -154, -500);
		enemy_placement(1, 0, -530, -154, -500);
		enemy_set_actives(2);
		player_placement(-470, 0, 1850);
		break;
	case 6 :
		load_model(o, (long*)LV6_DATA);
		clear_placement(1000, 0, -1500);
		crystals_placement(0,  520, 0,  1100, 0);
		crystals_placement(1, -520, 0,  1100, 1);
		crystals_placement(2,    0, 0,  1500, 2);
		crystals_placement(3,    0, 0, -2000, 3);
		crystals_placement(4, -500, 0, -1500, 4);
		crystals_placement(5,  500, 0, -1500, 5);
		crystals_set_actives(6);
		enemy_set_node(0,  0,    0,    0, 1500);
		enemy_set_node(0,  1,    0,    0, -2000);
		enemy_placement(0, 0, -530, -154, -500);
		enemy_set_actives(1);
		player_placement(1000, 0, 1000);
		break;
	case 7 :
		load_model(o, (long*)LV7_DATA);
		clear_placement(0, 0, 0);
		crystals_placement(0,  1000, 0,  -480, 0);
		crystals_placement(1, -1000, 0,  -480, 1);
		crystals_placement(2,  0, 0,  -1800, 2);
		crystals_placement(3,    500, 0, 1000, 3);
		crystals_set_actives(4);
		enemy_set_node(0,  0,  1800,   0,     0);
		enemy_set_node(0,  1,   480,   0,     0);
		enemy_set_node(1,  0,     0,   0,  1800);
		enemy_set_node(1,  1,     0,   0,   480);
		enemy_set_node(2,  0,     0,   0, -1800);
		enemy_set_node(2,  1,     0,   0,  -480);
		enemy_set_node(3,  0, -1800,   0,     0);
		enemy_set_node(3,  1,  -480,   0,     0);
		enemy_placement(0, 0, 1800, 0, 0);
		enemy_placement(1, 0, 0, 0,  1800);
		enemy_placement(2, 0, 0, 0, -1800);
		enemy_placement(3, 0, -1800, 0, 0);
		enemy_set_actives(4);
		player_placement(1, 0, 1);
		break;
	case 8 :
		load_model(o, (long*)LV8_DATA);
		clear_placement(0, 0, 1800);
		crystals_placement(0,  750, 0,  1850, 2);
		crystals_placement(1, -750, 0,  1850, 1);
		crystals_placement(2,  750, 0, -1750, 3);
		crystals_placement(3, -750, 0, -1750, 0);
		crystals_set_actives(4);
		enemy_set_node(0,  0,  800,  -154,    0);
		enemy_set_node(0,  1, -800,  -154,    0);
		enemy_set_node(1,  0,  800,  -154,  850);
		enemy_set_node(1,  1,  800,  -154, -850);
		enemy_set_node(2,  0, -800,  -154, -850);
		enemy_set_node(2,  1, -800,  -154,  850);
		enemy_placement(0, 0,  800,  -154,    0);
		enemy_placement(1, 1,  800,  -154,  -850);
		enemy_placement(2, 0, -800,  -154, -850);
		enemy_set_actives(3);
		player_placement(0, 0, 1800);
		break;
	/*case 9 : CANNED FOR MEMORY LIMITS (UNFINISHED AND BROKEN)
		load_model(o, (long*)LV9_DATA);
		clear_placement(0, 0, 1800);
		crystals_placement(0,  750, 0,  1850, 2);
		crystals_placement(1, -750, 0,  1850, 1);
		crystals_placement(2,  750, 0, -1750, 3);
		crystals_placement(3, -750, 0, -1750, 0);
		crystals_set_actives(4);
		enemy_set_node(0,  0,  800,  -154,    0);
		enemy_set_node(0,  1, -800,  -154,    0);
		enemy_set_node(1,  0,  800,  -154,  850);
		enemy_set_node(1,  1,  800,  -154, -850);
		enemy_set_node(2,  0, -800,  -154, -850);
		enemy_set_node(2,  1, -800,  -154,  850);
		enemy_placement(0, 0,  800,  -154,    0);
		enemy_placement(1, 1,  800,  -154,  -850);
		enemy_placement(2, 0, -800,  -154, -850);
		enemy_set_actives(3);
		player_placement(0, 0, 1800);
		break;*/
	case 9 :
		audio_stop(0);
		credit_screen();
		audio_play(0, -1);
		break;
	default:break;
	}

	player_on_level(i);
}

int main(int argc, char** argv)
{
	//GsSPRITE logo;
	obj_t lvl;
	int   i;
	int   lvl_select = 0;
	int   q = 1;
	long  song[5];

	render_init(250);
	pad_init();

	load_texture(FLOORTEX_DATA);
	load_texture(WALLTEX_DATA);
	load_texture(DISABLED_DATA);
    load_texture(ENABLED_DATA);
	load_texture(PLAYER_DATA);
	load_texture(OPPO_DATA);
	load_sprite(&credits, (long*)CREDITS_DATA);
	credits.scalex = ONE + ONE;
	credits.scaley = ONE + ONE;

	intro_screen();

	song[0] = C_DATA;
	//song[1] = SONG2_DATA;
	//song[2] = SONG3_DATA;
	//song[3] = SONG4_DATA;
	//song[4] = SONG5_DATA; ect.

	audio_init(song, 1, (long*)MIDIVH_DATA, (long*)MIDIVB_DATA);

	InitHeap((u_long*)FLOORTEX_DATA, (long)(MAIN_DATA-FLOORTEX_DATA));

	obj_init(&lvl);

	player_init();
	enemy_init();
	crystals_init();
	clear_init();

	FntLoad(960, 256);
	FntOpen(-96, -96, 192, 192, 0, 512);

	load_level(&lvl, 0);
	audio_play(0, -1);

	while(q)
	{
		pad_read();

		if (pad_button(PAD_START))
			q = 0;

		//if (pad_button_down(PAD_R2))
		//	audio_sfx_play(lvl_select, 48, 127);
		/*if (pad_button(PAD_L2))
			load_model(&lvl, (long*)DIADIS_DATA);
		*/
		//if (pad_button(PAD_R2))
		//	load_model(&lvl, (long*)CLEAR_DATA);


		if (crystals_all_active()) //|| pad_button_down(PAD_L2))
		{

			if (clear_checked())
			{
				audio_sfx_play(3, 48, 127);
				lvl_select = (lvl_select+1)%10;
				load_level(&lvl, lvl_select);
			}
			/*play collected all crystal sounds*/
		}

		if (enemy_on_player() || player_dead())
			load_level(&lvl, lvl_select);

		player_update();
		enemy_update();
		crystals_update();
		clear_update();

		render_begin();
			render_gdraw(&lvl.gsObjectHandler);
			player_render();
			enemy_render();
			crystals_render();
			clear_render();
		render_end();

		FntFlush(-1);
	}
	render_quit();
	audio_quit();
	return 0;
}
