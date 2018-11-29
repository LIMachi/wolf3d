/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/glfw_wrapper.h"
#include "../inc/env.h"

void	*print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	char *s;
	(void)win;
	(void)mod;
	printf("%s: %s\n", glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	if (key == GLFW_KEY_Q && act == GLFW_PRESS)
		glfwSetWindowShouldClose(win, 1);
	s = (char*)glfwGetKeyName(key, scan);
//	if (s != NULL && !strcmp(s, "m") && act == GLFW_PRESS)
//		map_editor();
	return (NULL);
}

void	center_cursor(GLFWwindow *win)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	glfwSetCursorPos(win, (double)width / 2.0, (double)height / 2.0);
}

void	*print_cursor_pos(GLFWwindow *win, double x, double y)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	printf("cursor pos: %.0f%% %.0f%%\n", (x / (double)width - 0.5) * 100.0, (0.5 - y / (double)height) * 100.0);
	center_cursor(win);
	return (NULL);
}

void	*print_mouse_button(GLFWwindow *win, int key, int act, int mod)
{
	(void)win;
	printf("key: %d, %s, %d\n", key, act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"), mod);
	return (NULL);
}

int	main(int ac, const char **av)
{
	t_glfw_env		e;
	t_glfw_window	*win;
	t_header		*map;
	int tick = 0;
	int second = (int)time(NULL);
	(void)set_env(&e);
	if (FT_Init_FreeType(&e.ft2_lib))
		return (-1);
	(void)av;
	if (ac == 2)
	{
		glfw_init();
		if ((win = glfw_new_window(SX, SY, "Wolf3d", NULL)) == NULL)
			return (-42);
		glfwSetKeyCallback(win->w, (GLFWkeyfun)&print_key);
		glfwSetMouseButtonCallback(win->w, (GLFWmousebuttonfun)&print_mouse_button);
		glfwSetCursorPosCallback(win->w, (GLFWcursorposfun)&print_cursor_pos);
		if ((map = load_map(av[1])) == NULL)
			if ((map = default_map()) == NULL)
				return (-1);
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
			if (glfwGetKey(win->w, GLFW_KEY_M))
				map_editor(map);
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
