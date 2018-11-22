/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:32:18 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdint.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <OpenGL/opengl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <time.h>
# include "../libft/libft.h"
#include "glfw_wrapper.h"

/*
** <stdint.h>
** typedef ... uint32_t
*/

typedef struct		s_header
{
	uint32_t		magic;
	uint32_t		height;
	uint32_t		width;
	uint32_t		startx;
	uint32_t		starty;
	uint32_t		look;
	uint8_t			map[0];
}					t_header;

// typedef struct		s_gl
// {
// 	// static const char	*fragment;
// 	// static const char	*vertex;
// 	unsigned char		*test;
// 	unsigned int		texture;
// 	unsigned int		vbo;
// 	unsigned int		vao;
// 	unsigned int		vs;
// 	unsigned int		fs;
// 	unsigned int		program;
// }					t_gl;



/*
** # define W3D_MAGIC *(uint32_t*)"w3d\n"
*/

t_header			*default_map(void);
t_header			*load_map(const char *path);
int					save_map(const char *path, t_header *header);
t_header			*map_editor(void);
t_glfw_window				*draw_map(t_glfw_window *win, t_header *map);

# define W3D_MAGIC	0x7733640A
#endif
