/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

uint32_t	get_pixel(t_glfw_window *win, uint32_t x, uint32_t y)
{
	uint32_t	out;

	if (win == NULL || x >= win->vb_width || y >= win->vb_height)
		return (0);
	out = 0;
	out |= (uint32_t)win->vb[(x + y * (win->vb_width + 1)) * 3] << 16;
	out |= (uint32_t)win->vb[(x + y * (win->vb_width + 1)) * 3 + 1] << 8;
	out |= (uint32_t)win->vb[(x + y * (win->vb_width + 1)) * 3 + 2];
	return (out);
}
