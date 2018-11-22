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

# define SX 1920
# define SY 1080

# define mSX 5
# define mSY 5

typedef struct				s_glfw_window
{
	struct s_glfw_window	*prev;
	struct s_glfw_window	*next;
	size_t					vb_width;
	size_t					vb_height;
	char					*vb;
	size_t					w_width;
	size_t					w_height;
	GLFWwindow				*w;
	GLuint					texture;
	GLuint					program;
	GLuint					vao;
}							t_glfw_window;

typedef struct				s_vec
{
	uint32_t				x;
	uint32_t				y;
}							t_vec;

typedef struct				s_glfw_env
{
	t_glfw_window			*window;
}							t_glfw_env;

t_glfw_env					*set_env(t_glfw_env *set);
t_glfw_env					*env(void);

void						glfw_init(void);
t_glfw_window				*glfw_new_window(size_t width,
											size_t length,
											char *name,
											void *user_ptr);
void						glfw_refresh_window(t_glfw_window *win);
void						glfw_remove_window(t_glfw_window *win);
t_glfw_window				*draw_square(t_glfw_window *win, t_vec pos, t_vec size, uint32_t color);
t_glfw_window				*draw_pixel(t_glfw_window *win, uint32_t x, uint32_t y, uint32_t color);

#endif
