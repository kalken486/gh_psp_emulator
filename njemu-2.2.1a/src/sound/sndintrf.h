/******************************************************************************

	sndintrf.c

	サウンドインタフェース

******************************************************************************/

#ifndef SOUND_INTERFACE_H
#define SOUND_INTERFACE_H

enum
{
	SOUND_YM2151_MONO = 0,
	SOUND_YM2151_STEREO,
	SOUND_YM2610,
	SOUND_QSOUND,
	SOUND_YM2151_CPS1,
	SOUND_TYPE_MAX
};

int sound_init(void);
void sound_exit(void);
void sound_reset(void);
void sound_mute(int mute);
void sound_update(INT16 *buffer);

#endif /* SOUND_INTERFACE_H */
