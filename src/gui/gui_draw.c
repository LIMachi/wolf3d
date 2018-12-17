/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp_file_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 19:34:13 by hmartzol          #+#    #+#             */
/*   Updated: 2016/12/18 23:30:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

static inline void	i_draw_cursor(t_glfw_window *win, t_button *button)
{
	int	t;

	if (button->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
	{
		t = (int)((double)button->active_bmp->size.x *
			(double)button->size.y / (double)button->active_bmp->size.y);
		draw_bmp(win, (t_int2){.x = button->pos.x + button->status - t / 2,
				.y = button->pos.y}, (t_int2){.x = t, .y = button->size.y},
			button->active_bmp);
	}
	else
	{
		t = (int)((double)button->active_bmp->size.y *
			(double)button->size.x / (double)button->active_bmp->size.x);
		draw_bmp(win, (t_int2){.y = button->pos.y + button->status - t / 2,
				.x = button->pos.x}, (t_int2){.y = t, .x = button->size.x},
			button->active_bmp);
	}
}

void				gui_draw(t_glfw_window *win, t_gui *gui)
{
	int			i;
	t_button	*button;

	i = -1;
	while (++i < gui->nb_buttons && (button = gui->buttons[i]) != NULL)
		if (button->type == BUTTON_TYPE_SLIDER_HORIZONTAL
			|| button->type == BUTTON_TYPE_SLIDER_VERTICAL)
		{
			if (button->hover)
				draw_bmp(win, button->pos, button->size, button->hover_bmp);
			else
				draw_bmp(win, button->pos, button->size, button->base_bmp);
			if (button->active_bmp != NULL)
				i_draw_cursor(win, button);
		}
		else if (button->hover)
			draw_bmp(win, button->pos, button->size, button->hover_bmp);
		else if (button->status)
		{
			if (button->type == BUTTON_TYPE_CLICK)
				button->status = 0;
			draw_bmp(win, button->pos, button->size, button->active_bmp);
		}
		else
			draw_bmp(win, button->pos, button->size, button->base_bmp);
}
