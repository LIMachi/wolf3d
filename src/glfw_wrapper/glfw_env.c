/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

/*
** glfw_env()->status == 1: ok
** glfw_env()->status == -1: error
** glfw_env()->status == 0: should not be possible to get
*/

t_glfw_env	*glfw_env(void)
{
	static t_glfw_env	env = {.status = 0, .window = NULL, .ft2_lib = NULL};

	if (env.status == 0)
	{
		if (FT_Init_FreeType(&env.ft2_lib) || glfwInit() == GLFW_FALSE)
		{
			env.status = -1;
			return (&env);
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_OPENGL_VERSION_MAJOR);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_OPENGL_VERSION_MINOR);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		env.status = 1;
	}
	return (&env);
}
