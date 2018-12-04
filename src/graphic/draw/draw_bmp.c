/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

t_glfw_window		*draw_bmp(t_glfw_window *win,
							t_vec pos,
							t_vec size,
							t_ubmp *ubmp)
{
	int			x;
	int			y;
	double		tx;
	double		ty;
	uint32_t	color;

	y = -1;
	while (++y < size.y && (x = -1))
		while (++x < size.x)
		{
			tx = (double)x * (double)ubmp->size.x / (double)size.x;
			ty = (double)y * (double)ubmp->size.y / (double)size.y;
			color = color_blend(color_blend(
				ubmp->data[(int)tx + 1 + ((int)ty + 1) * ubmp->size.x],
				ubmp->data[(int)tx + ((int)ty + 1) * ubmp->size.x], tx - (int)tx),
					color_blend(ubmp->data[(int)tx + 1 + (int)ty * ubmp->size.x],
						ubmp->data[(int)tx + (int)ty * ubmp->size.x], tx - (int)tx), ty - (int)ty);
			draw_pixel(win, x + pos.x, y + pos.y, color);
		}
	return (win);
}
