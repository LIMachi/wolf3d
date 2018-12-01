/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:33:49 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:30:38 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/glfw_wrapper.h"
#include "../../inc/env.h"

t_glfw_window		*draw_map(t_glfw_window *win,
							t_header *map)
{
	uint32_t		x;
	uint32_t		y;
	double			sx;
	double			sy;
	t_vector		look;

	x = -1;
	sx = (double)win->vb_width / (double)map->width;
	sy = (double)win->vb_height / (double)map->height;
	while (++x < map->width && (y = -1))
		while (++y < map->height)
			draw_square(win, (t_vec){(uint32_t)(x * sx), (uint32_t)(y * sy)},
				(t_vec){(uint32_t)sx, (uint32_t)sy},
				map->map[x + y * map->width] ? 0 : 0xFFFFFF);
	look = rotate_2d((t_vector){.x = 0, .y = -10}, (double)map->look / 100.0);
	draw_square(win,
		(t_vec){.x = map->startx * sx - 2, .y = map->starty * sy - 2},
		(t_vec){.x = 5, .y = 5}, 0xFF00);
	draw_line(win,
		(t_vec){.x = map->startx * sx, .y = map->starty * sy},
		(t_vec){.x = look.x + map->startx * sx, .y = look.y + map->starty * sy},
		0xFF0000);
	draw_text(win, (t_vec){.x = 2, .y = 2}, "this is a complicated text\nthat\t"
			"uses special characters\vto format itself", 0xFF0000);
	return (win);
}
