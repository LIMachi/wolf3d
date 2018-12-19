/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_load_animations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static t_sjson_error	i_texture(t_sjson_value *val, t_bmp **bmpa)
{
	t_sjson_string	*path;
	t_sjson_real	transparency;
	t_sjson_real	orientations;
	t_bmp			*tmp;
	size_t			i;

	path = NULL;
	tmp = NULL;
	transparency = -1;
	orientations = 255;
	sjson_explorer(val, "$o>r*$o>r*$o>s*", "transparency", &transparency,
		"orientations", &orientations, "file", &path);
	if (path == NULL || (tmp = bmp_file_load(path->data)) == NULL)
		return (SJSON_ERROR_KO);
	i = -1;
	while (++i < (size_t)(tmp->size.x * tmp->size.y))
		if (tmp->data[i] == (uint32_t)transparency)
			tmp->data[i] = 0xFF000000;
	i = -1;
	while (++i < 8)
		if ((1 << i) & (char)orientations)
			bmpa[i] = tmp;
	return (SJSON_ERROR_OK);
}

static t_sjson_error	i_textures(t_sjson_array *ar, t_animations *anim)
{
	size_t			i;
	size_t			j;
	t_sjson_array	*sar;

	if (ar->nb_values <= 0)
		return (SJSON_ERROR_OK);
	if ((anim->textures = malloc(sizeof(t_bmp*) * 8 * ar->nb_values)) == NULL)
		return (SJSON_ERROR_KO);
	anim->nb_textures = ar->nb_values;
	i = -1;
	while (++i < ar->nb_values)
	{
		if (sjson_explorer(ar->values[i], "$a*", &sar) != 1)
			continue ;
		j = -1;
		while (++j < sar->nb_values)
			i_texture(sar->values[j], &anim->textures[8 * i]);
	}
	return (SJSON_ERROR_OK);
}

static t_sjson_error	i_sounds(t_sjson_array *ar, t_animations *anim)
{
	size_t			i;
	t_sjson_string	*s;
	t_sound			*sound;

	i= -1;
	anim->nb_sounds = 0;
	while (++i < ar->nb_values)
		if (sjson_explorer(ar->values[i], "$s?") == 1)
			++anim->nb_sounds;
	if ((anim->sounds = malloc(sizeof(t_sound) * anim->nb_sounds)) == NULL)
		return (SJSON_ERROR_KO);
	anim->nb_sounds = 0;
	i = -1;
	while (++i < ar->nb_values)
		if (sjson_explorer(ar->values[i], "$s*", &s) == 1)
		{
			sound = &anim->sounds[anim->nb_sounds++];
			sound->data = drwav_open_and_read_file_f32(s->data,
				&sound->channels, &sound->sampleRate, &sound->totalSampleCount);
		}
	return (SJSON_ERROR_OK);
}

static t_sjson_error	i_frames(t_sjson_array *ar, t_animations *anim)
{
	(void)ar;
	(void)anim;
	return (SJSON_ERROR_OK);
}

t_sjson_error	assets_load_animation(const char *path, t_animations *anim)
{
	t_sjson_value	*root;

	if (sjson_parse_file(path, &root, SJSON_FLAG_PRINT_ERRORS, 2) != SJSON_ERROR_OK)
		return (SJSON_ERROR_KO);
//	sjson_print(2, root, 0);
//	printf("\n");
	sjson_explorer(root, "$o>a#$o>a#$o>>a#<o>a#<o>a#<o>a#<o>a#", "textures",
		i_textures, anim, "sounds", i_sounds, anim, "animations", "die",
		i_frames, anim->die, "hurt", i_frames, anim->hurt, "shoot", i_frames,
		anim->shoot, "stand", i_frames, anim->stand, "walk", i_frames,
		anim->walk);
	sjson_free(root);
	return (SJSON_ERROR_OK);
}
