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

	if ((env->map_file = malloc(
			sizeof(t_map_file) + 441 * sizeof(uint32_t))) == NULL)
		return (NULL);
	*env->map_file = (t_map_file){.magic = W3DM_MAGIC, .height = 21,
		.width = 21, .startx = 10, .starty = 10, .look = 0};
	i = -1;
	while (++i < 441)
		env->map_file->map[i] =
			i % 21 == 0 || i % 21 == 20 || i < 21 || i > 419;
	env->map_file->map[21 * 2 + 5] = 1;
	env->map_file->map[21 * 3 + 15] = 1;
	env->map_file->map[21 * 4 + 5] = 1;
	env->map_file->map[21 * 9 + 5] = 1;
	env->map_file->map[21 * 5 + 1] = 1;
	env->player.pos = (t_double2){.x = env->map_file->startx + 0.5,
								.y = env->map_file->starty + 0.5};
	env->player.look = (double)env->map_file->look / 100.0;
	return (env->map_file);
}
