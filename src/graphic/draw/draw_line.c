/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static inline void	draw_line_0(t_glfw_window *win,
								t_int2 v[4],
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
			draw_pixel(win, (uint32_t)v[0].x, (uint32_t)v[0].y, color);
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
			draw_pixel(win, (uint32_t)v[0].x, (uint32_t)v[0].y, color);
		}
}

t_glfw_window		*draw_line(t_glfw_window *win,
								t_int2 a,
								t_int2 b,
								uint32_t color)
{
	t_int2	d;
	t_int2	s;
	int		e;

	draw_pixel(win, (uint32_t)a.x, (uint32_t)a.y, color);
	if (a.x == b.x && a.y == b.y)
		return (win);
	d = (t_int2){.x = (b.x - a.x) << 1, .y = (b.y - a.y) << 1};
	s = (t_int2){.x = (d.x < 0) ? -1 : 1, .y = (d.y < 0) ? -1 : 1};
	d = (t_int2){.x = (d.x < 0) ? -d.x : d.x, (d.y < 0) ? -d.y : d.y};
	e = (d.x > d.y) ? d.y - (d.x >> 1) : d.x - (d.y >> 1);
	draw_line_0(win, (t_int2[4]){a, b, d, s}, e, color);
	return (win);
}
