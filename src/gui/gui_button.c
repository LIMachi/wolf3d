/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/12 15:09:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_button	gui_button_click(t_int2 pos,
							t_int2 size,
							t_button_update_callback cb,
							void *user_data)
{
	return ((t_button){.index = -1, .gui = NULL, .left = NULL, .right = NULL,
		.up = NULL, .down = NULL, .type = BUTTON_TYPE_CLICK, .pos = pos,
		.size = size, .status = 0, .hover = 0, .cb = cb, .hover_cb = NULL,
		.user_data = user_data, .active_bmp = NULL,
		.base_bmp = ft_bmp_default(), .hover_bmp = NULL});
}

t_button	gui_button_switch(t_int2 pos,
							t_int2 size,
							t_button_update_callback cb,
							void *user_data)
{
	return ((t_button){.index = -1, .gui = NULL, .left = NULL, .right = NULL,
		.up = NULL, .down = NULL, .type = BUTTON_TYPE_SWITCH, .pos = pos,
		.size = size, .status = 0, .hover = 0, .cb = cb, .hover_cb = NULL,
		.user_data = user_data, .active_bmp = NULL,
		.base_bmp = ft_bmp_default(), .hover_bmp = NULL});
}

t_button	gui_button_slider_horizontal(t_int2 pos,
										t_int2 size,
										t_button_update_callback cb,
										void *user_data)
{
	return ((t_button){.index = -1, .gui = NULL, .left = NULL, .right = NULL,
		.up = NULL, .down = NULL, .type = BUTTON_TYPE_SLIDER_HORIZONTAL,
		.pos = pos, .size = size, .status = 0, .hover = 0, .cb = cb,
		.user_data = user_data, .hover_cb = NULL,
		.active_bmp = ft_bmp_default(), .base_bmp = ft_bmp_default(),
		.hover_bmp = NULL});
}

t_button	gui_button_slider_vertical(t_int2 pos,
										t_int2 size,
										t_button_update_callback cb,
										void *user_data)
{
	return ((t_button){.index = -1, .gui = NULL, .left = NULL, .right = NULL,
		.up = NULL, .down = NULL, .type = BUTTON_TYPE_SLIDER_VERTICAL,
		.pos = pos, .size = size, .status = 0, .hover = 0, .cb = cb,
		.user_data = user_data, .hover_cb = NULL,
		.active_bmp = ft_bmp_default(), .base_bmp = ft_bmp_default(),
		.hover_bmp = NULL});
}
