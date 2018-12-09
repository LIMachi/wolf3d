/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/09 23:21:15 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	*print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	char *s;
	(void)win;
	(void)mod;
	printf("%s: %s\n", glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	if (key == GLFW_KEY_Q && act == GLFW_PRESS)
		glfwSetWindowShouldClose(win, 1);
	s = (char*)glfwGetKeyName(key, scan);
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
//	center_cursor(win);
	return (NULL);
}

void	*print_mouse_button(GLFWwindow *win, int key, int act, int mod)
{
	(void)win;
	printf("key: %d, %s, %d\n", key, act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"), mod);
	return (NULL);
}

void			draw(t_glfw_window *win)
{
	for (int x = 0; x < win->w_width; ++x)
		for (int y = 0; y < win->w_height; ++y)
			*((uint32_t*)&win->vb[(y * win->w_width + x) * 4]) = 0xFF0000;
	t_bmp	*bmp;
	bmp = bmp_file_load("assets/images/sprites/guard/die/1.bmp");
	draw_bmp(win, (t_vec){0, 0}, (t_vec){bmp->size.x * 2, bmp->size.y * 2}, bmp);
	free(bmp);
}

void	*resize(GLFWwindow *win, int x, int y)
{
	t_glfw_window	*w;

	w = glfwGetWindowUserPointer(win);
	w->w_height = y;
	w->w_width = x;
	glfw_window_resize_video_buffer(w, x, y);
	draw(w);
	return (w);
}

int	main(void)
{
	t_env	env;
	t_glfw_window	*win;
	int tick = 0;
	int second = (int)time(NULL);

	if ((win = glfw_new_window(SX, SY, "Wolf3d", NULL)) == NULL)
		return (-42);
	draw(win);
	glfwSetKeyCallback(win->w, (GLFWkeyfun)print_key);
	glfwSetMouseButtonCallback(win->w, (GLFWmousebuttonfun)print_mouse_button);
	glfwSetCursorPosCallback(win->w, (GLFWcursorposfun)print_cursor_pos);
	glfwSetFramebufferSizeCallback(win->w, (GLFWframebuffersizefun)resize);
	while (!glfwWindowShouldClose(win->w))
	{
		glfw_refresh_window(win);
		glfwPollEvents();
		if (glfwGetKey(win->w, GLFW_KEY_M))
			map_editor(&env);
		if (second != (int)time(NULL))
		{
			second = (int)time(NULL);
			printf("fps: %d\n", tick);
			tick = 0;
		}
		++tick;
	}
	glfwTerminate();
	return (0);
}
