/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_wrapper.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/13 19:33:11 by lmunoz-q         ###   ########.fr       */
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

# ifndef __WINDOWS__
#  define WORD uint16_t
#  define DWORD uint32_t
#  define LONG uint32_t
#  define O_BINARY 0
# endif

# define SX 1500
# define SY 1500

# define GLFW_OPENGL_VERSION_MAJOR 4
# define GLFW_OPENGL_VERSION_MINOR 0

# define PEN_DEFAULT_FONT "assets/fonts/Arial Unicode.ttf"
# define PEN_DEFAULT_PX_X 16
# define PEN_DEFAULT_PX_Y 16
# define PEN_DEFAULT_SPX_X 2
# define PEN_DEFAULT_SPX_Y 4
# define PEN_DEFAULT_COLOR 0x0

typedef struct							s_vec
{
	int									x;
	int									y;
}										t_vec;

# pragma pack(push, 1)

# define BITMAPSIGNATURE1 ((WORD)(('M' << 8) | 'B'))
# define BITMAPSIGNATURE2 ((WORD)(('A' << 8) | 'B'))

typedef struct							s_bitmap_file_header
{
	WORD								file_type;
	DWORD								file_size;
	DWORD								reserved;
	DWORD								offset;
}										t_bitmap_file_header;

/*
** unsuported format
*/

# define BITMAPCOREHEADER 12
# define OS21XBITMAPHEADER 12

/*
** supported format
*/

# define OS22XBITMAPHEADER 64
# define OS22XBITMAPHEADERV 16
# define BITMAPINFOHEADER 40
# define BITMAPV2INFOHEADER 52
# define BITMAPV3INFOHEADER 56

/*
** partially supported format
*/

# define BITMAPV4HEADER 108
# define BITMAPV5HEADER 124

/*
** supported compression
*/

# define BI_RGB 0
# define BI_BITFIELDS 3
# define BI_ALPHABITFIELDS 6

/*
** unsupported compression
*/

# define BI_RLE8 1
# define BI_RLE4 2
# define BI_JPEG 4
# define BI_PNG 5
# define BI_CMYK 11
# define BI_CMYKRLE8 12
# define BI_CMYKRLE4 13

typedef struct							s_dib
{
	DWORD								dib_size;
	LONG								width;
	LONG								height;
	WORD								planes;
	WORD								bit_per_pixel;
	DWORD								compression;
	DWORD								size_image;
	LONG								x_pixels_meter;
	LONG								y_pixels_meter;
	DWORD								palette;
	DWORD								color_important;
	DWORD								red_bmask;
	DWORD								green_bmask;
	DWORD								blue_bmask;
	DWORD								alpha_bmask;
	DWORD								color_space_type;
	char								color_space_endpoint[36];
	DWORD								gamma_red;
	DWORD								gamma_green;
	DWORD								gamma_blue;
	DWORD								intent;
	DWORD								icc_profile_data;
	DWORD								icc_profile_size;
	DWORD								reserved;
}										t_dib;

# pragma pack(pop)

typedef struct							s_bmp_file
{
	t_bitmap_file_header				head;
	t_dib								dib;
	uint32_t							*color_palette;
	uint8_t								*data;
}										t_bmp_file;

typedef	struct							s_bmp
{
	t_vec								size;
	uint32_t							data[0];
}										t_bmp;

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

typedef struct							s_pen
{
	t_vec								pos;
	t_vec								top_left;
	t_vec								bottom_right;
	uint32_t							color;
	FT_Face								font;
	t_vec								px;
	t_vec								spx;
}										t_pen;

/*
** types:
**  click (active only while the mouse button is held down)
**  toggle (switch state on each click)
**  slider (vertical or horizontal rectangle detecting click/drag)
**  composite slider (same as slider, but with additional click button)
**  text input (once clicked, catch keyboard input as text until esc is pressed
**   or click is detected elsewhere)
**  composite input (once clicked, change the behavior of keyboard and mouse)
*/

/*
** typedef enum				e_button_type
** {
** 	BUTTON_UNDEFINED = 0,
** 	BUTTON_CLICK,
** 	BUTTON_TOGGLE,
** 	BUTTON_SLIDER,
** 	BUTTON_COMPOSITE_SLIDER,
** 	BUTTON_TEXT_INPUT,
** 	BUTTON_COMPOSITE_INPUT
** }							t_button_type;
** void						button_click_callback(int status, t_vec pos)
** typedef struct				s_button_click
** {
**
** }							t_button_click;
** union						u_button
** {
** 	t_button_click			click;
** };
** typedef struct				s_button
** {
** 	t_vec					pos;
** 	t_vec					size;
** 	t_button_type			type;
** 	union u_button			button;
** }							t_button;
*/

typedef struct s_glfw_window			t_glfw_window;

typedef enum							e_mouse_status_action
{
	ACTION_MOVE = (unsigned int)-1,
	ACTION_SCROLL = (unsigned int)-2
}										t_mouse_status_action;

typedef struct							s_mouse_status
{
	t_mouse_status_action				last_action;
	int									button[GLFW_MOUSE_BUTTON_LAST + 1];
	double								pos_x;
	double								pos_y;
	double								scroll_x;
	double								scroll_y;
}										t_mouse_status;

typedef struct							s_keyboard_status
{
	int									last_key;
	int									last_scancode;
	int									key[GLFW_KEY_LAST + 1];
}										t_keyboard_status;

typedef enum							e_glfw_callback_flags_watch
{
	CFW_NONE = 0,
	CFW_KEYBOARD_DOWN = 1,
	CFW_KEYBOARD_UP = 2,
	CFW_KEYBOARD_REPEAT = 4,
	CFW_KEYBOARD = 7,
	CFW_MOUSE_DOWN = 8,
	CFW_MOUSE_UP = 16,
	CFW_MOUSE_CLICK = 24,
	CFW_MOUSE_MOVE = 32,
	CFW_MOUSE_SCROLL = 64
}										t_glfw_callback_flags_watch;

typedef enum							e_glfw_callback_flags_data
{
	CFD_NONE = 0,
	CFD_KEYBOARD,
	CFD_MOUSE
}										t_glfw_callback_flags_data;

/*
** int (*callback)(int id, void *data, void *user_data)
** if returned value is not zero, do not forward updates to other callbacks
*/

typedef int								(*t_glfw_callback)(int, void *, void *);

typedef struct s_glfw_callback_holder	t_glfw_callback_holder;
struct									s_glfw_callback_holder
{
	t_glfw_callback_holder				*prev;
	t_glfw_callback_holder				*next;
	t_glfw_callback_flags_watch			watch;
	t_glfw_callback_flags_data			data;
	t_vec								position;
	t_vec								size;
	int									id;
	void								*user_data;
	t_glfw_callback						cb;
};

struct									s_glfw_window
{
	struct s_glfw_window				*prev;
	struct s_glfw_window				*next;
	size_t								vb_width;
	size_t								vb_height;
	char								*vb;
	int									w_width;
	int									w_height;
	GLFWwindow							*w;
	GLuint								texture;
	GLuint								program;
	GLuint								vao;
	t_pen								pen;
	t_glfw_callback_holder				*callback;
	t_mouse_status						mouse;
	t_keyboard_status					keyboard;
	void								*user_ptr;
};

void									glfw_attach_callback(t_glfw_window *win,
													t_glfw_callback_holder *cb);

typedef struct							s_glfw_env
{
	int									status;
	t_glfw_window						*window;
	FT_Library							ft2_lib;
}										t_glfw_env;

t_glfw_env								*glfw_set_env(t_glfw_env *set);

t_glfw_env								*glfw_env(void);

void									glfw_update_callbacks(
											t_glfw_window *win,
											t_glfw_callback_flags_watch flags);

t_glfw_window							*glfw_new_window(size_t width,
														size_t length,
														char *name,
														void *user_ptr);

t_glfw_window							*glfw_window_resize_video_buffer(
															t_glfw_window *win,
															int x,
															int y);

void									glfw_callbacks(t_glfw_window *win);

t_bmp									*bmp_file_load(const char *path);

t_glfw_window							*draw_bmp(t_glfw_window *win,
													t_vec pos,
													t_vec size,
													t_bmp *bmp);

int										pen_init(t_glfw_window *win);

int										pen_set_font(t_glfw_window *win,
													const char *font_path,
													t_vec character_size,
													t_vec spacing);

int										pen_set_work_area(t_glfw_window *win,
														t_vec top_left,
														t_vec bottom_right);

void									glfw_refresh_window(t_glfw_window *win);

void									glfw_remove_window(t_glfw_window *win);

t_glfw_window							*draw_square(t_glfw_window *win,
													t_vec pos,
													t_vec size,
													uint32_t color);

t_glfw_window							*draw_pixel(t_glfw_window *win,
													uint32_t x,
													uint32_t y,
													uint32_t color);

t_glfw_window							*draw_line(t_glfw_window *win,
													t_vec a,
													t_vec b,
													uint32_t color);

uint32_t								color_blend(uint32_t c1,
													uint32_t c2,
													double f);

uint32_t								get_pixel(t_glfw_window *win,
													uint32_t x,
													uint32_t y);

t_vec									draw_char(t_glfw_window *win,
													t_vec pos,
													const char c,
													uint32_t color);

t_vec									draw_text(t_glfw_window *win,
													t_vec pos,
													char *text,
													uint32_t color);

void									*error(char *form, ...);

#endif
