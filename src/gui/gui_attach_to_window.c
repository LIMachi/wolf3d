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
			button->cb(win, (button->status ^= 1), button->user_data, button);
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
	glfwSetScrollCallback(win->w, gui_scroll_catch);
	glfwSetMouseButtonCallback(win->w, gui_button_catch);
	glfwSetKeyCallback(win->w, gui_key_catch);
	glfwSetCursorPosCallback(win->w, gui_cursor_pos_catch);
}
