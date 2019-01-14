/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:33:49 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/09 17:52:51 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

t_glfw_window		*draw_map(t_glfw_window *win,
							t_env *env)
{
	uint32_t		x;
	uint32_t		y;
	double			sx;
	double			sy;
	t_double2		look;

	x = -1;
	sx = (double)win->vb_width / (double)env->map_file->width;
	sy = (double)win->vb_height / (double)env->map_file->height;
	while (++x < env->map_file->width && (y = -1))
		while (++y < env->map_file->height)
			draw_square(win, (t_int2){(uint32_t)(x * sx), (uint32_t)(y * sy)},
				(t_int2){(uint32_t)sx, (uint32_t)sy},
				env->map_file->map[x + y * env->map_file->width] ?
				0 : 0xFFFFFF);
	look = rotate_2d((t_double2){.x = 0, .y = -10}, env->player.look);
	draw_square(win, (t_int2){.x = env->player.pos.x * sx - 2,
		.y = env->player.pos.y * sy - 2}, (t_int2){.x = 5, .y = 5}, 0xFF00);
	draw_line(win, (t_int2){.x = env->player.pos.x * sx,
		.y = env->player.pos.y * sy}, (t_int2){.x = look.x + env->player.pos.x *
		sx, .y = look.y + env->player.pos.y * sy}, 0xFF0000);
	return (win);
}
