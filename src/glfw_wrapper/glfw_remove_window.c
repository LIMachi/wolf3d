/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_remove_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:30:14 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 17:28:37 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/glfw_wrapper.h"

void	glfw_remove_window(t_glfw_window *win)
{
	glfwDestroyWindow(win->w);
	free(win->vb);
	if (win->prev != NULL)
		win->prev->next = win->next;
	if (win->next != NULL)
		win->next->prev = win->prev;
	if (win == env()->window)
		env()->window = win->next;
	if (env()->window != NULL)
	{
		glfwFocusWindow(env()->window->w);
		glfwMakeContextCurrent(env()->window->w);
	}
}
