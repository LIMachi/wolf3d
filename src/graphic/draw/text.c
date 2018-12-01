/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <ctype.h>

static inline t_vec		special(t_glfw_window *win, char c)
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
		win->pen.pos.x = win->pen.top_left.x;
	return (win->pen.pos);
}

static inline t_vec		draw_char_0(t_glfw_window *win,
									t_vec pos,
									FT_GlyphSlot glyph,
									FT_Bitmap bmp)
{
	t_vec		t;
	double		gray;

	t.x = -1;
	while (++t.x < (int)bmp.width && (t.y = -1))
		while (++t.y < (int)bmp.rows)
		{
			gray = 0.0;
			if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY)
				gray = (double)bmp.buffer[t.x + t.y * bmp.pitch] / 256.0;
			else if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY2)
				gray = (double)bmp.buffer[t.x + t.y * bmp.pitch] / 65536.0;
			else if (bmp.pixel_mode == FT_PIXEL_MODE_GRAY4)
				gray = (double)bmp.buffer[t.x + t.y * bmp.pitch] / 4294967296.0;
			else if (bmp.pixel_mode == FT_PIXEL_MODE_MONO)
				gray = (double)((bmp.buffer[(t.x >> 3) + t.y * bmp.pitch]
					& (1 << (t.x & 7))) != 0);
			draw_pixel(win, pos.x + t.x,
				pos.y + t.y + win->pen.px.y - win->pen.font->glyph->bitmap_top,
				color_blend(win->pen.color, get_pixel(win, pos.x + t.x,
					pos.y + t.y
					+ win->pen.px.y - win->pen.font->glyph->bitmap_top), gray));
		}
	return ((t_vec){.x = pos.x + ((t.x > (glyph->advance.x >> 6) || t.x == 0)
				? (glyph->advance.x >> 6) : t.x) + win->pen.spx.x, .y = pos.y});
}

t_vec					draw_char(t_glfw_window *win,
									const char c)
{
	FT_Bitmap		bmp;

	if (isspace(c))
		return (special(win, c));
	FT_Load_Char(win->pen.font, c, FT_LOAD_RENDER);
	if (win->pen.font->glyph->format != FT_GLYPH_FORMAT_BITMAP)
		return (win->pen.pos);
	bmp = win->pen.font->glyph->bitmap;
	if (bmp.pixel_mode != FT_PIXEL_MODE_GRAY
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY2
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY4
			&& bmp.pixel_mode != FT_PIXEL_MODE_MONO)
		return (win->pen.pos);
	win->pen.pos = draw_char_0(win, win->pen.pos, win->pen.font->glyph, bmp);
	return (win->pen.pos);
}

static inline t_vec		draw_word(t_glfw_window *win,
									char **word)
{
	FT_Bitmap		bmp;

	while (!iscntrl(**word) && !isspace(**word))
	{
		FT_Load_Char(win->pen.font, **word, FT_LOAD_RENDER);
		if (win->pen.font->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			return (win->pen.pos);
		bmp = win->pen.font->glyph->bitmap;
		if (bmp.pixel_mode != FT_PIXEL_MODE_GRAY
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY2
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY4
			&& bmp.pixel_mode != FT_PIXEL_MODE_MONO)
			return (win->pen.pos);
		++*word;
		win->pen.pos = draw_char_0(
								win, win->pen.pos, win->pen.font->glyph, bmp);
		if (win->pen.pos.x >= win->pen.bottom_right.x)
			special(win, '\n');
	}
	--*word;
	return (win->pen.pos);
}

static inline void		try_word(t_glfw_window *win,
								char *word)
{
	FT_Bitmap		bmp;
	FT_GlyphSlot	glyph;
	int				x;

	while (!iscntrl(*word) && !isspace(*word))
	{
		FT_Load_Char(win->pen.font, *word, FT_LOAD_RENDER);
		if (win->pen.font->glyph->format != FT_GLYPH_FORMAT_BITMAP)
			return ;
		bmp = win->pen.font->glyph->bitmap;
		glyph = win->pen.font->glyph;
		if (bmp.pixel_mode != FT_PIXEL_MODE_GRAY
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY2
			&& bmp.pixel_mode != FT_PIXEL_MODE_GRAY4
			&& bmp.pixel_mode != FT_PIXEL_MODE_MONO)
			return ;
		x = ((bmp.width > (glyph->advance.x >> 6) || bmp.width == 0)
			? (glyph->advance.x >> 6) : bmp.width) + win->pen.spx.x;
		if (win->pen.pos.x + x >= win->pen.bottom_right.x)
			break ;
		++word;
	}
	if (win->pen.pos.x + x >= win->pen.bottom_right.x)
		special(win, '\n');
}

t_vec					draw_text(t_glfw_window *win,
									t_vec pos,
									char *text,
									uint32_t color)
{
	win->pen.color = color;
	win->pen.pos = pos;
	while (*text != '\0')
	{
		if (isspace(*text))
		{
			if (text[0] == '\r' && text[1] == '\n')
				++text;
			special(win, *text);
		}
		else if (iscntrl(*text))
			draw_char(win, '.');
		else
		{
			try_word(win, text);
			draw_word(win, &text);
		}
		++text;
	}
	return (win->pen.pos);
}
