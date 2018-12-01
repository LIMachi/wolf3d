/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:32:18 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static void		*glfw_key(GLFWwindow *w,
							int key,
							int scancode,
							int action,
							...)
{
	t_glfw_window				*win;
	t_glfw_callback_flags_watch	flag;

	if ((win = glfwGetWindowUserPointer(w)) == NULL)
		return (NULL);
	win->keyboard.key[key] = action;
	win->keyboard.last_key = key;
	win->keyboard.last_scancode = scancode;
	flag = CFW_NONE;
	if (action == GLFW_PRESS)
		flag = CFW_KEYBOARD_DOWN;
	else if (action == GLFW_RELEASE)
		flag = CFW_KEYBOARD_UP;
	else if (action == GLFW_REPEAT)
		flag = CFW_KEYBOARD_REPEAT;
	glfw_update_callbacks(win, flag);
	return (NULL);
}

static void		*glfw_mouse_button(GLFWwindow *w,
									int button,
									int action,
									int mods)
{
	t_glfw_window				*win;
	t_glfw_callback_flags_watch	flag;

	(void)mods;
	if ((win = glfwGetWindowUserPointer(w)) == NULL)
		return (NULL);
	win->mouse.button[button] = action;
	win->mouse.last_action = button;
	flag = CFW_NONE;
	if (action == GLFW_PRESS)
		flag = CFW_MOUSE_DOWN;
	else if (action == GLFW_RELEASE)
		flag = CFW_MOUSE_UP;
	glfw_update_callbacks(win, flag);
	return (NULL);
}

static void		*glfw_mouse_pos(GLFWwindow *w,
								double xpos,
								double ypos)
{
	t_glfw_window				*win;

	if ((win = glfwGetWindowUserPointer(w)) == NULL)
		return (NULL);
	win->mouse.pos_x = xpos;
	win->mouse.pos_y = ypos;
	win->mouse.last_action = ACTION_MOVE;
	glfw_update_callbacks(win, CFW_MOUSE_MOVE);
	return (NULL);
}

static void		*glfw_mouse_scroll(GLFWwindow *w,
									double xoffset,
									double yoffset)
{
	t_glfw_window				*win;

	if ((win = glfwGetWindowUserPointer(w)) == NULL)
		return (NULL);
	win->mouse.scroll_x = xoffset;
	win->mouse.scroll_y = yoffset;
	win->mouse.last_action = ACTION_SCROLL;
	glfw_update_callbacks(win, CFW_MOUSE_SCROLL);
	return (NULL);
}

void			glfw_callbacks(t_glfw_window *win)
{
	glfwSetKeyCallback(win->w, (GLFWkeyfun)glfw_key);
	glfwSetMouseButtonCallback(win->w, (GLFWmousebuttonfun)glfw_mouse_button);
	glfwSetCursorPosCallback(win->w, (GLFWcursorposfun)glfw_mouse_pos);
	glfwSetScrollCallback(win->w, (GLFWscrollfun)glfw_mouse_scroll);
}
