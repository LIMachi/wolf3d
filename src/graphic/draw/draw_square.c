/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/10 16:21:40 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_glfw_window		*draw_square(t_glfw_window *win,
								t_int2 pos,
								t_int2 size,
								uint32_t color)
{
	int x;
	int y;

	x = -1;
	if (pos.x < 0)
	{
		size.x += pos.x;
		pos.x = 0;
	}
	if (pos.y < 0)
	{
		size.y += pos.y;
		pos.y = 0;
	}
	while (++x < size.x && x + pos.x < (ssize_t)win->vb_width)
	{
		y = -1;
		while (++y < size.y && y + pos.y < (ssize_t)win->vb_height)
			((uint32_t*)win->vb)[
				x + pos.x + (y + pos.y) * win->vb_width] = color;
	}
	return (win);
}
