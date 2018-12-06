/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_window_resize_video_buffer.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:10:15 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:36 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_glfw_window	*glfw_window_resize_video_buffer(t_glfw_window *win,
												int x,
												int y)
{
	if (win == NULL || x < 0 || y < 0)
		return (win);
	win->vb = reallocf(win->vb, x * y * sizeof(uint32_t));
	win->vb_width = (size_t)x;
	win->vb_height = (size_t)y;
	return (win);
}
