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

static void		gui_key_catch(GLFWwindow *w, int key, int scan, int act, int mod)
{
	t_glfw_window	*win;
	t_button		*button;

	win = glfwGetWindowUserPointer(w);
	if ((act != GLFW_PRESS && act != GLFW_REPEAT))
		win->key_cb(w, key, scan, act, mod);
	else
	{
		if (win->gui->selected != -1)
			button = win->gui->buttons[win->gui->selected];
		else
			button = NULL;
		if (key == GLFW_KEY_UP)
			if (button != NULL && button->type == BUTTON_TYPE_SLIDER_VERTICAL)
				button->cb(win, ++button->status, button->user_data, button);
			else
				win->gui->selected = button != NULL ? button->up->index : win->gui->down->index;
		else if (key == GLFW_KEY_DOWN)
			if (button != NULL && button->type == BUTTON_TYPE_SLIDER_VERTICAL)
				button->cb(win, --button->status, button->user_data, button);
			else
				win->gui->selected = button != NULL ? button->down->index : win->gui->up->index;
		else if (key == GLFW_KEY_LEFT)
			if (button != NULL && button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
				button->cb(win, --button->status, button->user_data, button);
			else
				win->gui->selected = button != NULL ? button->left->index : win->gui->right->index;
		else if (key == GLFW_KEY_RIGHT)
			if (button != NULL && button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
				button->cb(win, ++button->status, button->user_data, button);
			else
				win->gui->selected = button != NULL ? button->right->index : win->gui->left->index;
		else if (key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE)
			if (button != NULL)
				button->cb(win, button->status, button->user_data, button);
			else
				win->key_cb(w, key, scan, act, mod);
		else
			win->key_cb(w, key, scan, act, mod);
	}
}

static void		gui_button_catch(GLFWwindow *w, int key, int act, int mod)
{
	t_glfw_window	*win;
	t_button		*button;
	double			x;
	double			y;

	win = glfwGetWindowUserPointer(w);
	glfwGetCursorPos(w, &x, &y);
	if (key == GLFW_MOUSE_BUTTON_1 && act == GLFW_PRESS
		&& win->gui->selected != -1
		&& x >= (button = win->gui->buttons[win->gui->selected])->pos.x
		&& x < button->pos.x + button->size.x && y >= button->pos.y
		&& y < button->pos.y + button->size.y)
	{
		if (button->type == BUTTON_TYPE_CLICK)
			button->cb(win, 1, button->user_data, button);
		else if (button->type == BUTTON_TYPE_SWITCH)
			button->cb(win, button->status ^= 1, button->user_data, button);
		else
		{
			if (button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
				button->cb(win, button->status = x - button->pos.x,
					button->user_data, button);
			else if (button->type == BUTTON_TYPE_SLIDER_VERTICAL)
				button->cb(win, button->status = y - button->pos.y,
					button->user_data, button);
		}
	}
	else
		win->button_cb(w, key, act, mod);
}

static void		gui_cursor_pos_catch(GLFWwindow *w, double x, double y)
{
	t_glfw_window	*win;
	t_button		*button;
	int				i;

	win = glfwGetWindowUserPointer(w);
	if (win->gui->selected != -1)
		win->gui->buttons[win->gui->selected]->hover = 0;
	i = win->gui->nb_buttons;
	while (i--)
		if (x >= (button = win->gui->buttons[i])->pos.x && x < button->size.x
				&& y >= button->pos.y && x < button->size.y)
			break ;
	if (i != -1)
	{
		win->gui->selected = i;
		win->gui->buttons[i]->hover = 1;
	}
	else
		win->pos_cb(w, x, y);
}

static void		gui_scroll_catch(GLFWwindow *w, double x, double y)
{
	t_glfw_window	*win;
	t_button		*button;

	win = glfwGetWindowUserPointer(w);
	if (win->gui->selected == -1 ||
	(button = win->gui->buttons[win->gui->selected])->type == BUTTON_TYPE_CLICK
		|| button->type == BUTTON_TYPE_SWITCH)
	{
		win->scroll_cb(w, x, y);
		return ;
	}
	button->status += (int)x;
	button->cb(win, button->status, button->user_data, button);
}

void			gui_attach_to_window(t_glfw_window *win, t_gui *gui)
{
	win->gui = gui;
	gui->selected = -1;
	glfwSetScrollCallback(win->w, gui_scroll_catch);
	glfwSetMouseButtonCallback(win->w, gui_button_catch);
	glfwSetKeyCallback(win->w, gui_key_catch);
	glfwSetCursorPosCallback(win->w, gui_cursor_pos_catch);
}
