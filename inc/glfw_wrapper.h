/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_wrapper.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/20 20:25:53 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_WRAPPER_H
# define GLFW_WRAPPER_H

# include <stdint.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <OpenGL/opengl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <time.h>
# include "../libft/libft.h"

# define SX 1920
# define SY 1080

typedef struct				s_glfw_window
{
	struct s_glfw_window	*prev;
	struct s_glfw_window	*next;
	int						should_close;
	size_t					vb_width;
	size_t					vb_length;
	char					*vb;
	size_t					w_width;
	size_t					w_length;
	GLFWwindow				*w;
	GLuint					texture;
	GLuint					program;
	GLuint					vao;
}							t_glfw_window;

typedef struct				s_glfw_env
{
	t_glfw_window			*window;
}							t_glfw_env;

void						glfw_init(void);
t_glfw_window				*glfw_new_window(t_glfw_env *env,
											size_t width,
											size_t length,
											char *name);
void						glfw_refresh_window(t_glfw_window *win);

#endif