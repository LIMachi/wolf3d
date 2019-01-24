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

static inline int	i_up(t_glfw_window *win, t_button *button)
{
	if (button != NULL && button->type == BUTTON_TYPE_SLIDER_VERTICAL)
	{
		if (button->status < button->size.y - 1)
			button->cb(win, ++button->status, button->user_data, button);
	}
	else
	{
		if (button != NULL)
		{
			button->hover = 0;
			win->gui->selected = button->up->index;
		}
		else
			win->gui->selected = win->gui->down->index;
		win->gui->buttons[win->gui->selected]->hover = 1;
		win->gui->buttons[win->gui->selected]->hover_cb(win, -1,
			win->gui->buttons[win->gui->selected]->user_data,
			win->gui->buttons[win->gui->selected]);
	}
	return (0);
}

static inline int	i_down(t_glfw_window *win, t_button *button)
{
	if (button != NULL && button->type == BUTTON_TYPE_SLIDER_VERTICAL)
	{
		if (button->status > 0)
			button->cb(win, --button->status, button->user_data, button);
	}
	else
	{
		if (button != NULL)
		{
			button->hover = 0;
			win->gui->selected = button->down->index;
		}
		else
			win->gui->selected = win->gui->up->index;
		win->gui->buttons[win->gui->selected]->hover = 1;
		win->gui->buttons[win->gui->selected]->hover_cb(win, -1,
			win->gui->buttons[win->gui->selected]->user_data,
			win->gui->buttons[win->gui->selected]);
	}
	return (0);
}

static inline int	i_left(t_glfw_window *win, t_button *button)
{
	if (button != NULL && button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
	{
		if (button->status > 0)
			button->cb(win, --button->status, button->user_data, button);
	}
	else
	{
		if (button != NULL)
		{
			button->hover = 0;
			win->gui->selected = button->left->index;
		}
		else
			win->gui->selected = win->gui->right->index;
		win->gui->buttons[win->gui->selected]->hover = 1;
		win->gui->buttons[win->gui->selected]->hover_cb(win, -1,
			win->gui->buttons[win->gui->selected]->user_data,
			win->gui->buttons[win->gui->selected]);
	}
	return (0);
}

static inline int	i_right(t_glfw_window *win, t_button *button)
{
	if (button != NULL && button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
	{
		if (button->status < button->size.x - 1)
			button->cb(win, ++button->status, button->user_data, button);
	}
	else
	{
		if (button != NULL)
		{
			button->hover = 0;
			win->gui->selected = button->right->index;
		}
		else
			win->gui->selected = win->gui->left->index;
		win->gui->buttons[win->gui->selected]->hover = 1;
		win->gui->buttons[win->gui->selected]->hover_cb(win, -1,
			win->gui->buttons[win->gui->selected]->user_data,
			win->gui->buttons[win->gui->selected]);
	}
	return (0);
}

void				gui_key_catch(GLFWwindow *w,
								int key,
								int scan,
								int act)
{
	t_glfw_window		*win;
	t_button			*button;

	win = glfwGetWindowUserPointer(w);
	if ((act != GLFW_PRESS && act != GLFW_REPEAT))
		win->gui->key_cb(w, key, scan, act, 0);
	else
	{
		if (win->gui->selected != -1)
			button = win->gui->buttons[win->gui->selected];
		else
			button = NULL;
		key == GLFW_KEY_UP && i_up(win, button);
		key == GLFW_KEY_DOWN && i_down(win, button);
		key == GLFW_KEY_LEFT && i_left(win, button);
		key == GLFW_KEY_RIGHT && i_right(win, button);
		if (key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE)
			if (button != NULL)
				button->cb(win, button->type == BUTTON_TYPE_SWITCH ?
			button->status ^= 1 : button->status, button->user_data, button);
			else
				win->gui->key_cb(w, key, scan, act, 0);
		else
			win->gui->key_cb(w, key, scan, act, 0);
	}
}
