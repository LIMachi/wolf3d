/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/21 17:04:01 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/glfw_wrapper.h"

void	*print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	(void)win;
	(void)mod;
	printf("%s: %s\n", glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	return (NULL);
}

int	main(int ac, const char **av)
{
	t_glfw_env		env;
	t_glfw_window	*win;
	int tick = 0;
	int second = (int)time(NULL);
	(void)av;
	if (ac == 2)
	{
		glfw_init();
		if ((win = glfw_new_window(&env, SX, SY, "Wolf3d")) == NULL)
			return (-42);
		glfwSetKeyCallback(win->w, (GLFWkeyfun)&print_key);
		for (int x = 0; x < SX; ++x)
			for (int y = 0; y < SY; ++y)
			{
				win->vb[(y * SX + x) * 3] = rand() % 256;
				win->vb[(y * SX + x) * 3 + 1] = rand() % 256;
				win->vb[(y * SX + x) * 3 + 2] = rand() % 256;
			}
		while (!glfwWindowShouldClose(win->w))
		{
			for (int i = 0; i < SX * SY * 3; ++i)
				++win->vb[i];
			glfw_refresh_window(win);
			glfwPollEvents();
			if (second != (int)time(NULL))
			{
				second = (int)time(NULL);
				printf("fps: %d\n", tick);
				tick = 0;
			}
			++tick;
		}
		glfwTerminate();
	}
	else
		ft_putendl("Invalid Arguments");
	return (0);
}
