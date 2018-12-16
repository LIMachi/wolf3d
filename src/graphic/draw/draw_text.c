/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <ctype.h>

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
		draw_char(win, win->pen.pos, '\n', win->pen.color);
}

t_int2					draw_text(t_glfw_window *win,
									t_int2 pos,
									char *text,
									uint32_t color)
{
	--text;
	win->pen.pos = pos;
	while (*++text != '\0')
		if (isspace(*text))
		{
			if (text[0] == '\r' && text[1] == '\n')
				++text;
			draw_char(win, win->pen.pos, *text, color);
		}
		else if (iscntrl(*text))
			draw_char(win, win->pen.pos, '.', color);
		else
		{
			try_word(win, text);
			while (!iscntrl(*text) && !isspace(*text))
			{
				draw_char(win, win->pen.pos, *text, color);
				if (win->pen.pos.x >= win->pen.bottom_right.x)
					draw_char(win, win->pen.pos, '\n', color);
				++text;
			}
			--text;
		}
	return (win->pen.pos);
}
