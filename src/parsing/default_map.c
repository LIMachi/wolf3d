/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:18:52 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/09 17:44:00 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

/*
** <env.h>
** typedef struct s_header t_map_file
*/

t_map_file	*default_map(t_env *env)
{
	uint32_t				i;

	if (env->map_file != NULL)
		free(env->map_file);
	if ((env->map_file = malloc(
			sizeof(t_map_file) + 121 * sizeof(uint32_t))) == NULL)
		return (NULL);
	*env->map_file = (t_map_file){.magic = W3DM_MAGIC, .height = 11,
		.width = 11, .startx = 5, .starty = 5, .look = 0};
	i = -1;
	while (++i < 121)
		env->map_file->map[i] =
			i % 11 == 0 || i % 11 == 10 || i < 11 || i > 109;
	env->player.pos = (t_double2){.x = env->map_file->startx + 0.5,
								.y = env->map_file->starty + 0.5};
	env->player.look = (double)env->map_file->look / 100.0;
	return (env->map_file);
}
