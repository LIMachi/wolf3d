/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

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
			i = (int)(x + pos.x + (y + pos.y) * (win->vb_width + 1)) * 3;
			win->vb[i] = (char)(color >> 16);
			win->vb[i + 1] = (char)(color >> 8);
			win->vb[i + 2] = (char)color;
		}
	}
	return (win);
}
