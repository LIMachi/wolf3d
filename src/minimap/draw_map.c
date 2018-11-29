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

t_glfw_window		*draw_pixel(t_glfw_window *win,
								uint32_t x,
								uint32_t y,
								uint32_t color)
{
	if (win == NULL || x >= win->vb_width || y >= win->vb_height)
		return (win);
	win->vb[(x + y * (win->vb_width + 1)) * 3] = (color >> 16) & 0xFF;
	win->vb[(x + y * (win->vb_width + 1)) * 3 + 1] = (color >> 8) & 0xFF;
	win->vb[(x + y * (win->vb_width + 1)) * 3 + 2] = color & 0xFF;
	return (win);
}

t_glfw_window		*draw_square(t_glfw_window *win,
								t_vec pos,
								t_vec size,
								uint32_t color)
{
	int x;
	int y;
	int i;

	x = -1;
	while (++x < size.x && x < (ssize_t)win->vb_width)
	{
		y = -1;
		while (++y < size.y && y < (ssize_t)win->vb_height)
		{
			i = (x + pos.x + (y + pos.y) * (win->vb_width + 1)) * 3;
			win->vb[i] = (color >> 16) & 0xFF;
			win->vb[i + 1] = (color >> 8) & 0xFF;
			win->vb[i + 2] = color & 0xFF;
		}
	}
	return (win);
}

static inline void	draw_line_0(t_glfw_window *win,
								t_vec v[4],
								int e,
								uint32_t color)
{
	if (v[2].x > v[2].y)
		while (v[0].x != v[1].x)
		{
			if (e >= 0)
			{
				v[0].y += v[3].y;
				e -= v[2].x;
			}
			v[0].x += v[3].x;
			e += v[2].y;
			draw_pixel(win, v[0].x, v[0].y, color);
		}
	else
		while (v[0].y != v[1].y)
		{
			if (e >= 0)
			{
				v[0].x += v[3].x;
				e -= v[2].y;
			}
			v[0].y += v[3].y;
			e += v[2].x;
			draw_pixel(win, v[0].x, v[0].y, color);
		}
}

t_glfw_window		*draw_line(t_glfw_window *win,
								t_vec a,
								t_vec b,
								uint32_t color)
{
	t_vec	d;
	t_vec	s;
	int		e;

	draw_pixel(win, a.x, a.y, color);
	if (a.x == b.x && a.y == b.y)
		return (win);
	d = (t_vec){.x = (b.x - a.x) << 1, .y = (b.y - a.y) << 1};
	s = (t_vec){.x = (d.x < 0) ? -1 : 1, .y = (d.y < 0) ? -1 : 1};
	d = (t_vec){.x = (d.x < 0) ? -d.x : d.x, (d.y < 0) ? -d.y : d.y};
	e = (d.x > d.y) ? d.y - (d.x >> 1) : d.x - (d.y >> 1);
	draw_line_0(win, (t_vec[4]){a, b, d, s}, e, color);
	return (win);
}

t_glfw_window		*draw_map(t_glfw_window *win,
							t_header *map)
{
	uint32_t	x;
	uint32_t	y;
	double		sx;
	double		sy;
	t_vector	look;

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
	return (win);
}
