/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_update_callbacks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:32:18 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

inline void	glfw_update_callbacks(t_glfw_window *win,
								t_glfw_callback_flags_watch flags)
{
	t_glfw_callback_holder	*cbh;
	void					*data;

	cbh = win->callback;
	while (cbh != NULL)
	{
		if (cbh->watch & flags && win->mouse.pos_x >= cbh->position.x
			&& win->mouse.pos_x < cbh->position.x + cbh->size.x
			&& win->mouse.pos_y >= cbh->position.y
			&& win->mouse.pos_y < cbh->position.y + cbh->size.y)
		{
			data = NULL;
			if (cbh->data == CFD_KEYBOARD)
				data = (void*)&win->keyboard;
			if (cbh->data == CFD_MOUSE)
				data = (void*)&win->mouse;
			cbh->cb(cbh->id, data, cbh->user_data);
		}
		cbh = cbh->next;
	}
}
