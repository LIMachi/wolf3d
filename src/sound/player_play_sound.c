/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_play_sound.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

void	player_play_sound(t_sound *sound, t_sound_flags flags)
{
	t_sound_player	*player;

	if (flags == SOUND_NONE || sound == NULL
			|| (player = sound_player()) == NULL
			|| player->nb_sounds >= MAXIMUM_SOUND_SUPERPOSITION)
		return ;
	player->sound[player->nb_sounds] = sound;
	player->playing[player->nb_sounds] = (t_sound_playing){.flags = flags,
		.right_gain = 0.0, .left_gain = 0.0, .currentSample = 0,
		.left_phase = 0, .right_phase = sound->channels > 1};
	++player->nb_sounds;
}
