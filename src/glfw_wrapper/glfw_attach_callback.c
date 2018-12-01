/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_attach_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

void									glfw_attach_callback(t_glfw_window *win,
													t_glfw_callback_holder *cb)
{
	if (win == NULL)
		return ;
	cb->prev = NULL;
	if (win->callback != NULL)
	{
		win->callback->prev = cb;
		cb->next = win->callback;
	}
	else
		cb->next = NULL;
	win->callback = cb;
}
