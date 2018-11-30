/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:33:49 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:30:38 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/glfw_wrapper.h"
#include "../../inc/env.h"

t_glfw_window		*draw_map(t_glfw_window *win,
							t_header *map)
{
	uint32_t		x;
	uint32_t		y;
	double			sx;
	double			sy;
	t_vector		look;
	FT_GlyphSlot	slot;
	double			gray;

	x = -1;
	sx = (double)win->vb_width / (double)map->width;
	sy = (double)win->vb_height / (double)map->height;
	while (++x < map->width && (y = -1))
		while (++y < map->height)
			draw_square(win, (t_vec){(uint32_t)(x * sx), (uint32_t)(y * sy)},
				(t_vec){(uint32_t)sx, (uint32_t)sy},
				map->map[x + y * map->width] ? 0 : 0xFFFFFF);
	look = rotate_2d((t_vector){.x = 0, .y = -10}, (double)map->look / 100.0);
	draw_square(win,
		(t_vec){.x = map->startx * sx - 2, .y = map->starty * sy - 2},
		(t_vec){.x = 5, .y = 5}, 0xFF00);
	draw_line(win,
		(t_vec){.x = map->startx * sx, .y = map->starty * sy},
		(t_vec){.x = look.x + map->startx * sx, .y = look.y + map->starty * sy},
		0xFF0000);
	FT_Set_Pixel_Sizes(env()->font, 0, 128);
	slot = env()->font->glyph;
	FT_Load_Char(env()->font, 'a', FT_LOAD_RENDER);
	printf("pixel mode: %d\n", slot->bitmap.pixel_mode);
	for (x = 0; x < slot->bitmap.width; ++x)
		for (y = 0; y < slot->bitmap.rows; ++y)
			if (slot->bitmap.buffer[x + y * slot->bitmap.width])
			{
				gray = (double)slot->bitmap.buffer[x + y * slot->bitmap.width] / 256.0;
				draw_pixel(win, x, y, color_blend(0xFF, 0xFFFFFF, gray));
			}
	return (win);
}
