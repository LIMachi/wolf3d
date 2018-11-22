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

t_glfw_window	*draw_pixel(t_glfw_window *win, uint32_t x, uint32_t y, uint32_t color)
{
	if (win == NULL || x >= win->vb_width || y >= win->vb_height)
		return (win);
	win->vb[x + y * win->vb_width * 3] = (color >> 16) & 0xFF;
	win->vb[x + y * win->vb_width * 3 + 1] = (color >> 8) & 0xFF;
	win->vb[x + y * win->vb_width * 3 + 2] = color & 0xFF;
	return (win);
}

t_glfw_window	*draw_square(t_glfw_window *win, t_vec pos, t_vec size, uint32_t color)
{
	uint32_t x;
	uint32_t y;

	x = -1;
	while (++x < size.x)
	{
		y = -1;
		while (++y < size.y)
			draw_pixel(win, x + pos.x, y + pos.y, color);
	}
	return (win);
}

t_glfw_window	*draw_map(t_glfw_window *win, t_header *map)
{
	uint32_t	x;
	uint32_t	y;
	double		sx;
	double		sy;

	x = -1;
	sx = (double)win->vb_width / (double)map->width;
	sy = (double)win->vb_height / (double)map->height;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
			draw_square(win, (t_vec){(uint32_t)(x * sx), (uint32_t)(y * sy)}, (t_vec){(uint32_t)sx, (uint32_t)sy}, map->map[x + y * map->width] ? 0xFFFFFF : 0);
	}
	return (win);
}
