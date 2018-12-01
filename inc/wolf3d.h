/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:32:18 by lmunoz-q         ###   ########.fr       */
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
# include <time.h>
# include <math.h>
# include "../libft/libft.h"
# include "glfw_wrapper.h"

/*
** <stdint.h>
** typedef ... uint32_t
*/

# define RAD_TO_DEG (180.0 / M_PI)
# define DEG_TO_RAD (M_PI / 180.0)

# define W3DM_MAGIC	0x7733646D
# define W3DS_MAGIC 0x77336473
# define W3DC_MAGIC 0x77336463

# define MASK_FLAG_MOUSE_BUTTON (((uint32_t)1) << 31)

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

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
	t_vector		pos;
	double			look;
}					t_player;

typedef struct		s_config_file
{
	uint32_t		magic;
	uint32_t		forward;
	uint32_t		backward;
	uint32_t		strafe_left;
	uint32_t		strafe_right;
	uint32_t		turn_left;
	uint32_t		turn_right;
	uint32_t		action;
}					t_config_file;

typedef struct		s_save_file
{
	uint32_t		magic;
	t_player		player;
	t_config_file	config_file;
	t_map_file		map_file;
}					t_save_file;

typedef struct		s_env
{
	t_map_file		*map_file;
	t_config_file	*config_file;
	t_player		player;
}					t_env;

t_map_file			*default_map(void);
t_map_file			*load_map(const char *path);
int					save_map(const char *path, t_map_file *header);
t_map_file			*map_editor(t_map_file *out);
t_glfw_window		*draw_map(t_glfw_window *win, t_map_file *map);
t_vector			rotate_2d(t_vector vec, double deg);

#endif
