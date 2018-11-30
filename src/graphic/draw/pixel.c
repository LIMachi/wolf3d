/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_glfw_window		*draw_pixel(t_glfw_window *win,
	uint32_t x,
	uint32_t y,
	uint32_t color)
{
	if (win == NULL || x >= win->vb_width || y >= win->vb_height)
		return (win);
	win->vb[(x + y * (win->vb_width + 1)) * 3] = (char)(color >> 16);
	win->vb[(x + y * (win->vb_width + 1)) * 3 + 1] = (char)(color >> 8);
	win->vb[(x + y * (win->vb_width + 1)) * 3 + 2] = (char)color;
	return (win);
}
