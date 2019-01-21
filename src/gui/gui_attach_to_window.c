/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_attach_to_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/12 15:09:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static inline void	gui_button_slider(t_glfw_window *win, t_button *button,
									double x, double y)
{
	if (button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
		button->cb(win, button->status = x - button->pos.x,
			button->user_data, button);
	else if (button->type == BUTTON_TYPE_SLIDER_VERTICAL)
		button->cb(win, button->status = y - button->pos.y,
			button->user_data, button);
}

static void			gui_button_catch(GLFWwindow *w, int key, int act, int mod)
{
	t_glfw_window	*win;
	t_button		*button;
	double			x;
	double			y;
	int				t[2];

	win = glfwGetWindowUserPointer(w);
	glfwGetCursorPos(w, &x, &y);
	glfwGetWindowSize(win->w, &t[0], &t[1]);
	x *= (double)win->vb_width / (double)t[0];
	y *= (double)win->vb_height / (double)t[1];
	if (key == GLFW_MOUSE_BUTTON_1 && act == GLFW_PRESS
		&& win->gui->selected != -1
		&& x >= (button = win->gui->buttons[win->gui->selected])->pos.x
		&& x < button->pos.x + button->size.x && y >= button->pos.y
		&& y < button->pos.y + button->size.y)
	{
		if (button->type == BUTTON_TYPE_CLICK)
			button->cb(win, 1, button->user_data, button);
		else if (button->type == BUTTON_TYPE_SWITCH)
			button->cb(win, (button->status ^= 1), button->user_data, button);
		else
			gui_button_slider(win, button, x, y);
	}
	else
		win->gui->button_cb(w, key, act, mod);
}

static void			gui_scroll_catch(GLFWwindow *w, double x, double y)
{
	t_glfw_window	*win;
	t_button		*button;

	win = glfwGetWindowUserPointer(w);
	if (win->gui->selected == -1 ||
	(button = win->gui->buttons[win->gui->selected])->type == BUTTON_TYPE_CLICK
		|| button->type == BUTTON_TYPE_SWITCH)
	{
		win->gui->scroll_cb(w, x, y);
		return ;
	}
	button->status += (int)x;
	button->cb(win, button->status, button->user_data, button);
}

static inline void	clean_callbacks(t_glfw_window *win,
	t_gui *gui,
	int keep_original_callbacks)
{
	gui->scroll_cb = glfwSetScrollCallback(win->w, gui_scroll_catch);
	gui->button_cb = glfwSetMouseButtonCallback(win->w, gui_button_catch);
	gui->key_cb = glfwSetKeyCallback(win->w, (GLFWkeyfun)gui_key_catch);
	gui->pos_cb = glfwSetCursorPosCallback(win->w, gui_cursor_pos_catch);
	if (!keep_original_callbacks || gui->scroll_cb == NULL)
		gui->scroll_cb = (GLFWscrollfun)noop;
	if (!keep_original_callbacks || gui->key_cb == NULL)
		gui->key_cb = (GLFWkeyfun)noop;
	if (!keep_original_callbacks || gui->button_cb == NULL)
		gui->button_cb = (GLFWmousebuttonfun)noop;
	if (!keep_original_callbacks || gui->pos_cb == NULL)
		gui->pos_cb = (GLFWcursorposfun)noop;
}

void				gui_attach_to_window(t_glfw_window *win,
	t_gui *gui,
	int keep_original_callbacks)
{
	int	i;

	win->gui = gui;
	gui->selected = -1;
	i = gui->nb_buttons;
	while (i--)
	{
		if (gui->buttons[i]->up == NULL)
			gui->buttons[i]->up = gui->up;
		if (gui->buttons[i]->down == NULL)
			gui->buttons[i]->down = gui->down;
		if (gui->buttons[i]->left == NULL)
			gui->buttons[i]->left = gui->left;
		if (gui->buttons[i]->right == NULL)
			gui->buttons[i]->right = gui->right;
	}
	clean_callbacks(win, gui, keep_original_callbacks);
}
