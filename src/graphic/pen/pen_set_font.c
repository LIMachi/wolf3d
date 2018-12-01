/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pen_set_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

int	pen_set_font(t_glfw_window *win,
				const char *font_path,
				t_vec character_size,
				t_vec spacing)
{
	if (win == NULL || font_path == NULL || character_size.x < 1
			|| character_size.y < 1 || spacing.x < 0 || spacing.y < 0)
		return (-1);
	if (win->pen.font != NULL)
		FT_Done_Face(win->pen.font);
	if (FT_New_Face(glfw_env()->ft2_lib, font_path, 0, &win->pen.font))
		return (-1);
	if (FT_Set_Pixel_Sizes(win->pen.font, character_size.x, character_size.y))
		return (-1);
	win->pen.px = character_size;
	win->pen.spx = spacing;
	return (0);
}
