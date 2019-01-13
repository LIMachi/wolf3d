/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <math.h>

static inline void	i_portaudio_callback(float *out, t_sound_player *player)
{
	long			i;
	t_sound_playing	*play;

	out[0] = 0;
	out[1] = 0;
	i = -1;
	while (++i < player->nb_sounds && (play = &player->playing[i]) != NULL)
	{
		if (play->currentSample * player->sound[i]->channels
				>= player->sound[i]->totalSampleCount)
		{
			play->currentSample = 0;
			if (play->flags == SOUND_PLAY_ONCE)
				play->flags = SOUND_NONE;
		}
		if (play->flags == SOUND_NONE)
			break ;
		out[0] += pow(10.0, play->left_gain / 10.0) *
			player->sound[i]->data[play->left_phase +
			play->currentSample * player->sound[i]->channels];
		out[1] += pow(10.0, play->right_gain / 10.0) *
			player->sound[i]->data[play->right_phase +
			play->currentSample * player->sound[i]->channels];
		++play->currentSample;
	}
}

static int			portaudio_callback(const void *input,
	void *output,
	unsigned long fpb,
	const PaStreamCallbackTimeInfo *ti,
	PaStreamCallbackFlags flags,
	void *user_ptr)
{
	t_sound_player	*player;
	float			*out;
	unsigned long	i;
	unsigned long	j;

	(void)ti;
	(void)flags;
	(void)input;
	out = (float*)output;
	player = (t_sound_player*)user_ptr;
	for(i = 0; i < fpb; ++i)
	{
		i_portaudio_callback(out, player);
		out += 2;
	}
	j = 0;
	for(i = 0; (int)i < player->nb_sounds; ++i)
		if (player->playing[i].flags != SOUND_NONE)
			player->playing[j++] = player->playing[i];
	player->nb_sounds = (int)j;
	return (paContinue);
}

t_sound_player		*sound_player(void)
{
	static t_sound_player	player = {.stream = NULL, .nb_sounds = 0};
	int						i;

	if (player.stream == NULL)
	{
		if (paNoError != Pa_Initialize())
			return (NULL);
		if ((player.param.device = Pa_GetDefaultOutputDevice()) == paNoDevice)
			return (NULL);
		i = -1;
		while (++i < MAXIMUM_SOUND_SUPERPOSITION)
		{
			player.sound[i] = NULL;
			player.playing[i] = (t_sound_playing){.flags = SOUND_NONE};
		}
		player.param.channelCount = 2;
		player.param.sampleFormat = paFloat32;
		player.param.suggestedLatency =
			Pa_GetDeviceInfo(player.param.device)->defaultLowOutputLatency;
		player.param.hostApiSpecificStreamInfo = NULL;
		Pa_OpenStream(&player.stream, NULL, &player.param, 44100, 0, paClipOff,
			portaudio_callback, &player);
		Pa_StartStream(player.stream);
	}
	return (&player);
}

void				sound_player_finish(void)
{
	t_sound_player	*player;

	if ((player = sound_player()) != NULL)
	{
		Pa_StopStream(player->stream);
		Pa_CloseStream(player->stream);
		Pa_Terminate();
	}
}
