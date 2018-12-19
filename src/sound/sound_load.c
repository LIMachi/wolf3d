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
		&sound.sampleRate, &sound.totalSampleCount);
	return (sound);
}

void	sound_unload(t_sound *sound)
{
	sound->channels = 0;
	drwav_free(sound->data);
	sound->data = NULL;
	sound->sampleRate = 0;
	sound->totalSampleCount = 0;
}
