/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <ctype.h>

static inline t_int2		special(t_glfw_window *win, char c)
{
	if (c == ' ' || c == '\t')
	{
		win->pen.pos.x += win->pen.spx.x * 4 * (1 + 3 * (c == '\t'));
		if (win->pen.pos.x >= win->pen.bottom_right.x)
			c = '\n';
	}
	if (c == '\v' || c == '\f' || c == '\r' || c == '\n')
		win->pen.pos.y += win->pen.px.y + win->pen.spx.y;
	if (c == '\r' || c == '\n')
		win->pen.pos.x = win->pen.top_left.x + win->pen.spx.x;
	return (win->pen.pos);
}

static inline double	gray(FT_Bitmap bmp, int x, int y)
{
	if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY)
		return ((double)bmp.buffer[x + y * bmp.pitch] / 256.0);
	else if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY2)
		return ((double)bmp.buffer[x + y * bmp.pitch] / 65536.0);
	else if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY4)
		return ((double)bmp.buffer[x + y * bmp.pitch] / 4294967296.0);
	else if (bmp.pixel_mode == FT_PIXEL_MODE_MONO)
		return ((double)((bmp.buffer[(x >> 3) + y * bmp.pitch]
			& (1 << (x & 7))) != 0));
	else
		return (0.0);
}

static inline t_int2		draw_char_0(t_glfw_window *win,
									t_int2 pos,
									FT_GlyphSlot glyph,
									FT_Bitmap bmp)
{
	int			x;
	int			y;
	int			tx;
	int			ty;

	x = -1;
	while (++x < (int)bmp.width && (y = -1))
		while (++y < (int)bmp.rows)
		{
			tx = pos.x + x;
			ty = pos.y + y + win->pen.px.y - win->pen.font->glyph->bitmap_top;
			if (tx >= win->pen.top_left.x && tx < win->pen.bottom_right.x
				&& ty >= win->pen.top_left.y && ty < win->pen.bottom_right.y)
				draw_pixel(win, tx, ty, color_blend(win->pen.color,
					get_pixel(win, tx, ty), gray(bmp, x, y)));
		}
	return ((t_int2){.x = pos.x + ((x > (glyph->advance.x >> 6) || x == 0)
		? (glyph->advance.x >> 6) : x) + win->pen.spx.x, .y = pos.y});
}

t_int2					draw_char(t_glfw_window *win,
								t_int2 pos,
								const char c,
								uint32_t color)
{
	FT_Bitmap		bmp;
	FT_GlyphSlot	glyph;

	win->pen.pos = pos;
	win->pen.color = color;
	if (isspace(c))
		return (special(win, c));
	FT_Load_Char(win->pen.font, c, FT_LOAD_RENDER);
	if (win->pen.font->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		return (win->pen.pos);
	glyph = win->pen.font->glyph;
	bmp = glyph->bitmap;
	if (bmp.pixel_mode != FT_PIXEL_MODE_GRAY
		&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY2
		&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY4
		&& bmp.pixel_mode != FT_PIXEL_MODE_MONO)
		return (win->pen.pos);
	win->pen.pos = draw_char_0(win, win->pen.pos, win->pen.font->glyph, bmp);
	return (win->pen.pos);
}
