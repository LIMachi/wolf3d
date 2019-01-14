/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_glfw_window		*draw_clear(t_glfw_window *win, uint32_t color)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < win->vb_height)
	{
		x = -1;
		while (++x < win->vb_width)
			((uint32_t*)win->vb)[x + y * win->vb_width] = color;
	}
	return (win);
}
