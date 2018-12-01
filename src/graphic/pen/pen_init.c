/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pen_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

int	pen_init(t_glfw_window *win)
{
	if (win == NULL || pen_set_work_area(win, (t_vec){.x = 0, .y = 0},
			(t_vec){.x = win->vb_width, .y = win->vb_height})
			|| pen_set_font(win, PEN_DEFAULT_FONT,
			(t_vec){PEN_DEFAULT_PX_X, PEN_DEFAULT_PX_Y},
			(t_vec){PEN_DEFAULT_SPX_X, PEN_DEFAULT_SPX_Y}))
		return (-1);
	win->pen.pos = win->pen.spx;
	win->pen.color = PEN_DEFAULT_COLOR;
	return (0);
}
