/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_attach_button.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/12 15:09:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static inline void	i_gui_attach_to_other_buttons_vertical(t_gui *gui,
															t_button *button)
{
	if (button->up != NULL)
	{
		if (button->up->down != NULL)
		{
			button->up->down->up = button;
			button->down = button->up->down;
		}
		button->up->down = button;
	}
	else if (button->down != NULL)
	{
		if (button->down->up != NULL)
		{
			button->down->up->down = button;
			button->up = button->down->up;
		}
		button->down->up = button;
	}
	if (button->down == gui->up)
		gui->up = button;
	if (button->up == gui->down)
		gui->down = button;
}

static inline void	i_gui_attach_to_other_buttons_horizontal(t_gui *gui,
															t_button *button)
{
	if (button->right != NULL)
	{
		if (button->right->left != NULL)
		{
			button->right->left->right = button;
			button->left = button->right->left;
		}
		button->right->left = button;
	}
	else if (button->left != NULL)
	{
		if (button->left->right != NULL)
		{
			button->left->right->left = button;
			button->right = button->left->right;
		}
		button->left->right = button;
	}
	if (button->right == gui->left)
		gui->left = button;
	if (button->left == gui->right)
		gui->right = button;
}

static inline void	i_gui_attach_to_other_buttons(t_gui *gui, t_button *button)
{
	int i;

	i = gui->nb_buttons;
	button->right = NULL;
	button->left = NULL;
	button->up = NULL;
	button->down = NULL;
	while (i--)
	{
		if (button->pos.x < gui->buttons[i]->pos.x)
			button->right = gui->buttons[i];
		if (button->pos.x + button->size.x
				> gui->buttons[i]->pos.x + gui->buttons[i]->size.x)
			button->left = gui->buttons[i];
		if (button->pos.y < gui->buttons[i]->pos.y)
			button->down = gui->buttons[i];
		if (button->pos.y + button->size.y
				> gui->buttons[i]->pos.y + gui->buttons[i]->size.y)
			button->up = gui->buttons[i];
	}
	i_gui_attach_to_other_buttons_horizontal(gui, button);
	i_gui_attach_to_other_buttons_vertical(gui, button);
}

int					gui_attach_button(t_gui *gui, t_button *button)
{
	button->index = gui->nb_buttons;
	button->gui = gui;
	button->status = (button->type == BUTTON_TYPE_CLICK);
	button->hover = 0;
	if (gui->nb_buttons == 0)
	{
		gui->right = button;
		gui->left = button;
		gui->down = button;
		gui->up = button;
	}
	i_gui_attach_to_other_buttons(gui, button);
	if ((gui->buttons = reallocf(gui->buttons,
			++gui->nb_buttons * sizeof(t_button*))) == NULL)
		return (-1);
	gui->buttons[button->index] = button;
	return (0);
}
