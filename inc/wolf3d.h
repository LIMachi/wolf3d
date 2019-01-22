/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/09 23:37:47 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <stdint.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <OpenGL/opengl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include "glfw_wrapper.h"
# include <sjson.h>

# define WOLF3D_ASSETS_JSON_PATH "assets/assets.json"
# define WOLF3D_CONFIG_W3C_PATH "config.w3c"
# define WOLF3D_DEFAULT_WINDOW_SIZE ((t_int2){.x = 1920, .y = 1080})
# define WOLF3D_DEFAULT_WINDOW_NAME "Wolf3D"

/*
** <stdint.h>
** typedef ... uint32_t
*/

# define RAD_TO_DEG (180.0 / M_PI)
# define DEG_TO_RAD (M_PI / 180.0)

/*
** map: w3dm
** save: w3ds
** config: w3dc
*/

# define W3DM_MAGIC	0x7733646D
# define W3DS_MAGIC 0x77336473
# define W3DC_MAGIC 0x77336463

# define MASK_FLAG_MOUSE_BUTTON (((uint32_t)1) << 31)

typedef struct		s_raycast
{
	int 			drawstart;
	int 			drawend;
	int				face;
	int				mapx;
	int				mapy;
	int 			floor;
	int 			sky;
	int 			tx;
	int 			ty;
	int 			stepx;
	int 			stepy;
	int 			hit;
	double 			dx;
	double 			dy;
	double			where;
	double 			fov;
	double			dist;
	double 			cdist;
	double			hauteur;
	double			angle;
	double			real;
	double 			floorx;
	double 			floory;
	double			cfx;
	double 			cfy;
	double 			fact;
	t_bmp			*texture;
	t_bmp			*texturen2;
	t_bmp			*skybox;
	t_double2		firsthit;
}					t_raycast;

typedef struct		s_map_file
{
	uint32_t		magic;
	uint32_t		height;
	uint32_t		width;
	uint32_t		startx;
	uint32_t		starty;
	uint32_t		look;
	uint8_t			map[0];
}					t_map_file;

typedef struct		s_player
{
	t_double2		pos;
	double			look;
}					t_player;

typedef struct		s_config_file
{
	uint32_t		magic;
	int32_t			forward;
	int32_t			backward;
	int32_t			strafe_left;
	int32_t			strafe_right;
	int32_t			turn_left;
	int32_t			turn_right;
	int32_t			action;
	uint32_t		fov;
}					t_config_file;

typedef struct		s_save_file
{
	uint32_t		magic;
	int32_t			posx;
	int32_t			posy;
	int32_t			look;
	t_config_file	config_file;
	t_map_file		map_file;
}					t_save_file;

/*
** sound == -1 do nothing
** sound >= 0 start a sound
** texture_index == -1 end of animation
*/

typedef struct		s_animation_frame
{
	int				texture_index;
	double			speed;
	int				interuptible;
	int				sound;
}					t_animation_frame;

/*
** layout: *textures[o + 8 * i] i == nb_frames, o == orientation
*/

typedef struct		s_animations
{
	size_t				nb_textures;
	t_bmp				**textures;
	size_t				nb_sounds;
	t_sound				*sounds;
	t_animation_frame	*die;
	t_animation_frame	*hurt;
	t_animation_frame	*shoot;
	t_animation_frame	*stand;
	t_animation_frame	*walk;
}					t_animations;

/*
typedef struct		s_assets
{
	int				nb_animations;
	t_animations	*animations;
	char			**anmination_names;
	int				nb_fonts;
	char			**fonts;
	char			**font_names;
	int				nb_musics;
	t_sound			*musics;
	char			**music_names;
	int				nb_textures;
	t_bmp			**textures;
	char			**texture_names;
}					t_assets;
*/

typedef struct		s_assets
{
	t_swt_map		animations; //path -> file (cache)
	t_swt_map		animations_names; //name -> path (id)
	t_swt_map		fonts_names;
	t_swt_map		sounds;
	t_swt_map		sounds_names;
	t_swt_map		textures;
	t_swt_map		textures_names;
}					t_assets;

/*
** contextes:
*/

# define W3DC_INIT				0
# define W3DC_MAIN_MENU			1
# define W3DC_NEW_GAME_MENU		2
# define W3DC_PLAYING			3
# define W3DC_PLAYING_MENU		4
# define W3DC_LOAD_GAME_MENU	5
# define W3DC_MAP_EDITOR		6
# define W3DC_MAP_EDITOR_MENU	7
# define W3DC_OPTIONS_MENU		8
# define W3DC_CREDITS			9
# define W3DC_EXIT				-1
# define W3D_DEBUG				-2

typedef struct		s_env
{
	t_map_file		*map_file;
	t_config_file	config_file;
	t_player		player;
	int				context;
	int				prev_context;
	t_glfw_window	*wolf3d;
	t_glfw_window	*minimap;
	t_assets		assets;
	double			music_volume;
	void			*user_ptr;
}					t_env;

void				context_swap(t_env *env);
int					set_context(t_env *env, int context);

int					context_init_load(t_env *env);
void				context_main_menu_load(t_env *env);
void				context_end(t_env *env);
void				context_playing_load(t_env *env);
void				context_playing_loop(t_env *env);
void				context_new_game_menu_load(t_env *env);
void				context_in_game_menu_load(t_env *env);
void				context_load_game_menu_load(t_env *env);
void				context_options_menu_load(t_env *env);

t_assets			assets_load(const char *path);
t_sjson_error		assets_load_animation(const char *path, t_animations *anim);
t_bmp				*assets_get_texture(t_assets *assets, char *id, char *path);
t_sound				*assets_get_sound(t_assets *assets, char *id, char *path);
void				assets_unload(t_assets *assets);

t_map_file			*default_map(t_env *env);
t_map_file			*load_map(const char *path, t_env *env);
int					save_map(const char *path, t_map_file *header);
int					get_maps_in_dir(const char *dirpath, char **buf,
									size_t buf_size);

int					save(const char *path, t_env *env);
int					load(const char *path, t_env *env);
int					get_saves_in_dir(const char *dirpath, char **buf,
									size_t buf_size);

t_config_file		*default_config(t_env *env);
t_config_file		*load_config(const char *path, t_env *env);
int					save_config(const char *path, t_config_file *config_file);

t_env				*map_editor(t_env *env);
t_glfw_window		*draw_map(t_glfw_window *win, t_env *env);
t_double2			rotate_2d(t_double2 vec, double deg);

#endif
