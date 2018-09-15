/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/09/15 21:11:12 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

// #include "glfw-3.2.1/glad/include/glad/glad.h"
// #include "glfw-3.2.1/include/GLFW/glfw3.h"

#include "../inc/env.h"
#include "../libft/libft.h"

#define SX 1200
#define SY 600

int	main(int ac, const char **av)
{
	// t_env	env;

	(void)av;
	if (ac == 2)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		GLFWwindow* window = glfwCreateWindow(1400, 600, "Hello World\n", NULL, NULL);
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
	else
		ft_putendl("Invalid Arguments");
	return (0);
}
