/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:28:11 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:28:14 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	minimap(t_env *env)
{
	uint32_t		x;
	uint32_t		y;
	int				sx;
	int				sy;
	t_double2		look;

	x = -1;
	sx = (env->wolf3d->vb_width / 6.0) / env->map_file->width;
	sy = (env->wolf3d->vb_height / 6.0) / env->map_file->height;
	while (++x < env->map_file->width && (y = -1))
		while (++y < env->map_file->height)
			if (env->map_file->map[x + y * env->map_file->width])
				draw_square(env->wolf3d, (t_int2){(uint32_t)(x * sx), (uint32_t)
				(y * sy)}, (t_int2){(uint32_t)sx, (uint32_t)sy}, 0);
	look = rotate_2d((t_double2){.x = 0, .y = -10}, env->player.look);
	draw_square(env->wolf3d, (t_int2){.x = env->player.pos.x * sx - 2,
		.y = env->player.pos.y * sy - 2}, (t_int2){.x = 5, .y = 5}, 0xFF0000);
	draw_line(env->wolf3d, (t_int2){.x = env->player.pos.x * sx,
		.y = env->player.pos.y * sy}, (t_int2){.x = look.x + env->player.pos.x *
		sx, .y = look.y + env->player.pos.y * sy}, 0xFF0000);
}
