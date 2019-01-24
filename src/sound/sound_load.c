/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_sound	sound_load(const char *path)
{
	t_sound	sound;

	sound.data = drwav_open_and_read_file_f32(path, &sound.channels,
		&sound.sample_rate, &sound.total_sample_count);
	return (sound);
}

void	sound_unload(t_sound *sound)
{
	t_sound_player	*player;
	int				i;

	player = sound_player();
	i = -1;
	while (++i < player->nb_sounds)
		if (player->sound[i] == sound)
		{
			while (++i < player->nb_sounds - 1)
			{
				player->playing[i - 1] = player->playing[i];
				player->sound[i - 1] = player->sound[i];
			}
			player->playing[i] = (t_sound_playing){.flags = SOUND_NONE,
				.right_phase = 0, .left_phase = 0, .current_sample = 0,
				.left_gain = 0.0, .right_gain = 0.0};
			player->sound[i] = NULL;
		}
	sound->channels = 0;
	drwav_free(sound->data);
	sound->data = NULL;
	sound->sample_rate = 0;
	sound->total_sample_count = 0;
}
