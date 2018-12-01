/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <glfw_wrapper.h>

t_header	*map_scale(t_header *map, uint32_t width, uint32_t height)
{
	t_header	*out;
	uint32_t	x;
	uint32_t	y;

	if (width == map->width && height == map->height)
		return (map);
	if ((out = malloc(sizeof(t_header) + width * height)) == NULL)
	{
		free(map);
		return (NULL);
	}
	*out = (t_header){.magic = W3D_MAGIC, .height = height, .width = width,
		.startx = width / 2, .starty = height / 2, .look = 0};
	y = -1;
	while (++y < height && y < map->height)
	{
		x = -1;
		while (++x < width && map->width)
			out->map[x + y * width] = map->map[x + y * map->width];
	}
	free(map);
	return (out);
}

void		click_block(t_glfw_window *win, t_header *map, double x, double y)
{
	double			sx;
	double			sy;
	size_t			i;

	sx = (double)win->w_width / (double)map->width;
	sy = (double)win->w_height / (double)map->height;
	i = (size_t)(x / sx) + (size_t)(y / sy) * map->width;
	map->map[i] ^= 1;
}

void		*click(GLFWwindow *win, int key, int act, int mod)
{
	double			x;
	double			y;
	t_glfw_window	*u_win;

	(void)mod;
	u_win = glfwGetWindowUserPointer(win);
	if (key == GLFW_MOUSE_BUTTON_1 && act == GLFW_PRESS)
	{
		glfwGetWindowSize(win, &u_win->w_width, &u_win->w_height);
		glfwGetCursorPos(win, &x, &y);
		if (x < 0.0 || y < 0.0 || x > (double)u_win->w_width
				|| y > (double)u_win->w_height)
			return (NULL);
		click_block(u_win, u_win->user_ptr, x, y);
	}
	return (NULL);
}

t_header	*map_editor(t_header *out)
{
	t_glfw_window	*win;

	if (out == NULL && (out = default_map()) == NULL)
		return (NULL);
	if ((win = glfw_new_window(out->width * 25, out->height * 25,
					"map editor", out)) == NULL)
	{
		free(out);
		return (NULL);
	}
	glfwSetMouseButtonCallback(win->w, (GLFWmousebuttonfun) & click);
	while (!glfwWindowShouldClose(win->w))
	{
		draw_map(win, out);
		glfw_refresh_window(win);
		glfwPollEvents();
		if (glfwGetKey(win->w, GLFW_KEY_S) == GLFW_PRESS)
			save_map("test.w3d", out);
	}
	glfw_remove_window(win);
	return (out);
}
