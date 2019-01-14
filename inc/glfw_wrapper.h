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
# include "../libft/inc/libft.h"
# include "portaudio.h"
# include "../portaudio/dr_wav/dr_wav.h"
# include "../glfw-3.2.1/freetype-2.9.1/include/ft2build.h"

# include FT_FREETYPE_H

/*
** https://www.freetype.org/freetype2/docs/tutorial/step1.html
*/

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
	t_int2								pos;
	t_int2								top_left;
	t_int2								bottom_right;
	uint32_t							color;
	FT_Face								font;
	t_int2								px;
	t_int2								spx;
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
** void						button_click_callback(int status, t_int2 pos)
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
** 	t_int2					pos;
** 	t_int2					size;
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
	t_int2								position;
	t_int2								size;
	int									id;
	void								*user_data;
	t_glfw_callback						cb;
};

/*
** button types:
** sinlge click
** toggle
** slider (vertical, horizontal)
*/

/*
** basic button ellement:
** left, right, up, down reference of other button
** type
** position
** size
** status (1 for click or toggle, any integer for slider)
** hover/selected
** update callback
** user data
*/

typedef enum							e_button_type
{
	BUTTON_TYPE_CLICK,
	BUTTON_TYPE_SWITCH,
	BUTTON_TYPE_SLIDER_HORIZONTAL,
	BUTTON_TYPE_SLIDER_VERTICAL
}										t_button_type;

typedef struct s_button					t_button;
typedef struct s_gui					t_gui;

typedef void							(*t_button_update_callback)(
											t_glfw_window *,
											int,
											void *,
											t_button *);

struct									s_button
{
	int									index;
	t_gui								*gui;
	t_button							*left;
	t_button							*right;
	t_button							*up;
	t_button							*down;
	t_button_type						type;
	t_int2								pos;
	t_int2								size;
	int									status;
	int									hover;
	t_button_update_callback			cb;
	t_button_update_callback			hover_cb;
	void								*user_data;
	t_bmp								*base_bmp;
	t_bmp								*hover_bmp;
	t_bmp								*active_bmp;
};

/*
** active_bmp is used in switch and click as a replacement for base_bmp
** but will be used as a cursor for sliders
*/

/*
** gui:
** current button: index (hover/selected)
** nb buttons: int
** buttons: (reference to all buttons)
** forward callback key
** forward callback pointer
** forward callback button
*/

struct									s_gui
{
	int									selected;
	int									nb_buttons;
	t_button							**buttons;
	t_button							*up;
	t_button							*down;
	t_button							*left;
	t_button							*right;
	GLFWmousebuttonfun					button_cb;
	GLFWcursorposfun					pos_cb;
	GLFWscrollfun						scroll_cb;
	GLFWkeyfun							key_cb;
};

/*
** functions needed:
** create button
** add button to gui
** attach gui to window
*/

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
	t_gui								*gui;
};

/*
** t_sound are treated as being const and should not be modified
*/

typedef struct		s_sound
{
	float			*data;
	unsigned int	channels;
	unsigned int	sampleRate;
	drwav_uint64	totalSampleCount;
}					t_sound;

#define MAXIMUM_SOUND_SUPERPOSITION 10

typedef enum		e_sound_flags
{
	SOUND_NONE,
	SOUND_LOOP,
	SOUND_PLAY_ONCE
}					t_sound_flags;

typedef struct		s_sound_playing
{
	t_sound_flags	flags;
	float			left_gain;
	float			right_gain;
	drwav_uint64	left_phase;
	drwav_uint64	right_phase;
	unsigned int	currentSample;
}					t_sound_playing;

typedef struct		s_sound_player
{
	PaStream			*stream;
	PaStreamParameters	param;
	int					nb_sounds;
	t_sound				*sound[MAXIMUM_SOUND_SUPERPOSITION];
	t_sound_playing		playing[MAXIMUM_SOUND_SUPERPOSITION];
}					t_sound_player;

t_sound_player							*sound_player(void);
void									sound_player_finish(void);
void									sound_unload(t_sound *sound);
t_sound									sound_load(const char *path);
void									player_play_sound(t_sound *sound,
														t_sound_flags flags);

void									noop(void);

void									gui_key_catch(GLFWwindow *w,
													int key,
													int scan,
													int act);

void									gui_cursor_pos_catch(GLFWwindow *w,
															double x,
															double y);

t_gui									gui_gui(void);

void									gui_attach_to_window(t_glfw_window *win,
												t_gui *gui,
												int keep_original_callbacks);

void									gui_draw(t_glfw_window *win,
												t_gui *gui);


int										gui_attach_button(t_gui *gui,
														t_button *button);

t_button								gui_button_click(t_int2 pos,
													t_int2 size,
													t_button_update_callback cb,
													void *user_data);

t_button								gui_button_switch(t_int2 pos,
													t_int2 size,
													t_button_update_callback cb,
													void *user_data);

t_button								gui_button_slider_horizontal(t_int2 pos,
													t_int2 size,
													t_button_update_callback cb,
													void *user_data);

t_button								gui_button_slider_vertical(t_int2 pos,
													t_int2 size,
													t_button_update_callback cb,
													void *user_data);

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
													t_int2 pos,
													t_int2 size,
													t_bmp *bmp);

t_glfw_window							*draw_clear(t_glfw_window *win,
													uint32_t color);

int										pen_init(t_glfw_window *win);

int										pen_set_font(t_glfw_window *win,
													const char *font_path,
													t_int2 character_size,
													t_int2 spacing);

int										pen_set_work_area(t_glfw_window *win,
														t_int2 top_left,
														t_int2 bottom_right);

void									glfw_refresh_window(t_glfw_window *win);

void									glfw_remove_window(t_glfw_window *win);

t_glfw_window							*draw_square(t_glfw_window *win,
													t_int2 pos,
													t_int2 size,
													uint32_t color);

t_glfw_window							*draw_pixel(t_glfw_window *win,
													uint32_t x,
													uint32_t y,
													uint32_t color);

t_glfw_window							*draw_line(t_glfw_window *win,
													t_int2 a,
													t_int2 b,
													uint32_t color);

uint32_t								color_blend(uint32_t c1,
													uint32_t c2,
													double f);

uint32_t								get_pixel(t_glfw_window *win,
													uint32_t x,
													uint32_t y);

t_int2									draw_char(t_glfw_window *win,
													t_int2 pos,
													const char c,
													uint32_t color);

t_int2									draw_text(t_glfw_window *win,
													t_int2 pos,
													char *text,
													uint32_t color);

void									*error(char *form, ...);

#endif
