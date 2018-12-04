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
	center_cursor(win);
	return (NULL);
}

void	*print_mouse_button(GLFWwindow *win, int key, int act, int mod)
{
	(void)win;
	printf("key: %d, %s, %d\n", key, act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"), mod);
	return (NULL);
}

int test_mouse(int id, t_mouse_status *mouse, void *data)
{
	(void)id;
	(void)data;
	printf("detected mouse %f %f\n", mouse->pos_x, mouse->pos_y);
	return (0);
}

int	main(int ac, const char **av)
{
	t_glfw_window	*win;
	t_map_file		*map;
	t_glfw_callback_holder	test_cbh = {
		.cb = NULL,
		.user_data = NULL,
		.data = CFD_MOUSE,
		.watch = CFW_MOUSE_MOVE,
		.size = (t_vec){.x = SX / 2, .y = SY / 2},
		.position = (t_vec){.x = SX / 4, .y = SY / 4},
		.id = 0};
	int tick = 0;
	int second = (int)time(NULL);

	(void)av;
	test_cbh.cb = (t_glfw_callback)&test_mouse;
	if (ac == 2)
	{
		if ((win = glfw_new_window(SX, SY, "Wolf3d", NULL)) == NULL)
			return (-42);
		glfw_attach_callback(win, &test_cbh);
		if ((map = load_map(av[1])) == NULL)
			if ((map = default_map()) == NULL)
				return (-1);
		for (int x = 0; x < SX; ++x)
			for (int y = 0; y < SY; ++y)
				*((uint32_t*)&win->vb[(y * SX + x) * 4]) = 0xFF0000;
		t_bitmap	*bitmap = bmp_file_load("assets/images/bmp0_test_image.bmp");
		t_ubmp		*bmp = bmp_decompress(bitmap);
		free(bitmap);
		draw_bmp(win, (t_vec){10, 10}, (t_vec){bmp->size.x * 5.5, bmp->size.y * 5.5}, bmp);
		free(bmp);
		while (!glfwWindowShouldClose(win->w))
		{
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
