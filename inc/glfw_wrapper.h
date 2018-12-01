/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_wrapper.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_WRAPPER_H
# define GLFW_WRAPPER_H

# include <stdint.h>
# include "../glfw-3.2.1/glad/include/glad/glad.h"
# include "../glfw-3.2.1/include/GLFW/glfw3.h"
# include <OpenGL/opengl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <time.h>
# include "../libft/libft.h"
# include "../glfw-3.2.1/freetype-2.9.1/include/ft2build.h"
# include FT_FREETYPE_H

/*
** https://www.freetype.org/freetype2/docs/tutorial/step1.html
*/

# define SX 1920
# define SY 1080

# define GLFW_OPENGL_VERSION_MAJOR 4
# define GLFW_OPENGL_VERSION_MINOR 0

# define PEN_DEFAULT_FONT "/Library/Fonts/Arial.ttf"
# define PEN_DEFAULT_PX_X 16
# define PEN_DEFAULT_PX_Y 16
# define PEN_DEFAULT_SPX_X 2
# define PEN_DEFAULT_SPX_Y 4
# define PEN_DEFAULT_COLOR 0x0

typedef struct				s_vec
{
	int						x;
	int						y;
}							t_vec;

/*
** t_pen:
**  pos: current position of the pen
**  top_left: top_left limit of the pen movement
**  bottom_right: bottom_right limit of the pen movement
**  color: color to be used
**  font: font id
**  px: size of character
**  spx: sparation beetween character, x used horizontaly and y vertically
**   one space will be interpreted as spx.x * 4
**   one tab will be interpreted as spx.x * 16
**   \v\f\n\r vertical jump will be interpreted as ps.y + spx.y
*/

typedef struct				s_pen
{
	t_vec					pos;
	t_vec					top_left;
	t_vec					bottom_right;
	uint32_t				color;
	FT_Face					font;
	t_vec					px;
	t_vec					spx;
}							t_pen;

typedef struct				s_glfw_window
{
	struct s_glfw_window	*prev;
	struct s_glfw_window	*next;
	size_t					vb_width;
	size_t					vb_height;
	char					*vb;
	int						w_width;
	int						w_height;
	GLFWwindow				*w;
	GLuint					texture;
	GLuint					program;
	GLuint					vao;
	t_pen					pen;
	void					*user_ptr;
}							t_glfw_window;

typedef struct				s_glfw_env
{
	int						status;
	t_glfw_window			*window;
	FT_Library				ft2_lib;
}							t_glfw_env;

t_glfw_env					*glfw_set_env(t_glfw_env *set);

t_glfw_env					*glfw_env(void);

void						glfw_init(void);

t_glfw_window				*glfw_new_window(size_t width,
											size_t length,
											char *name,
											void *user_ptr);

int							pen_init(t_glfw_window *win);

int							pen_set_font(t_glfw_window *win,
										const char *font_path,
										t_vec character_size,
										t_vec spacing);

int							pen_set_work_area(t_glfw_window *win,
												t_vec top_left,
												t_vec bottom_right);

void						glfw_refresh_window(t_glfw_window *win);

void						glfw_remove_window(t_glfw_window *win);

t_glfw_window				*draw_square(t_glfw_window *win,
										t_vec pos,
										t_vec size,
										uint32_t color);

t_glfw_window				*draw_pixel(t_glfw_window *win,
										uint32_t x,
										uint32_t y,
										uint32_t color);

t_glfw_window				*draw_line(t_glfw_window *win,
										t_vec a,
										t_vec b,
										uint32_t color);

uint32_t					color_blend(uint32_t c1,
										uint32_t c2,
										double f);

uint32_t					get_pixel(t_glfw_window *win,
										uint32_t x,
										uint32_t y);

t_vec						draw_char(t_glfw_window *win,
										t_vec pos,
										const char c,
										uint32_t color);

t_vec						draw_text(t_glfw_window *win,
										t_vec pos,
										char *text,
										uint32_t color);

#endif
