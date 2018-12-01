/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

int	init_pen(t_glfw_window *win)
{
	win->pen = (t_pen){.pos = {1, 1}, .top_left = {1, 1},
		.bottom_right = {win->vb_width - 1, win->w_height - 1},
		.color = 0, .font = NULL, .px = {16, 16}, .spx = {2, 4}};
	if (FT_New_Face(env()->ft2_lib, "/Library/Fonts/Arial.ttf",
					0, &win->pen.font))
		return (-1);
	FT_Set_Pixel_Sizes(win->pen.font, 16, 16);
	return (0);
}
