/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_cursor_pos_catch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/12 15:09:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static inline void	i_update_slider(t_glfw_window *win,
	double x,
	double y,
	t_button *button)
{
	if (glfwGetMouseButton(win->w, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS)
		return ;
	if (button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
		button->cb(win, button->status = x - button->pos.x,
			button->user_data, button);
	else
		button->cb(win, button->status = y - button->pos.y,
			button->user_data, button);
}

void				gui_cursor_pos_catch(GLFWwindow *w, double x, double y)
{
	t_glfw_window	*win;
	t_button		*button;
	int				i;

	win = glfwGetWindowUserPointer(w);
	if (win->gui->selected != -1)
		win->gui->buttons[win->gui->selected]->hover = 0;
	i = win->gui->nb_buttons;
	while (i--)
		if (x >= (button = win->gui->buttons[i])->pos.x
			&& x < button->pos.x + button->size.x
			&& y >= button->pos.y && y < button->pos.y + button->size.y)
			break ;
	if (i != -1)
	{
		win->gui->selected = i;
		button = win->gui->buttons[win->gui->selected];
		button->hover = 1;
		button->hover_cb(win, -1, button->user_data, button);
		if (button->type == BUTTON_TYPE_SLIDER_VERTICAL
				|| button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
			i_update_slider(win, x, y, button);
	}
	else
		win->gui->pos_cb(w, x, y);
}
