/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_editor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/10 16:16:11 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <glfw_wrapper.h>

t_map_file	*map_scale(t_map_file *map, uint32_t width, uint32_t height)
{
	t_map_file	*out;
	uint32_t	x;
	uint32_t	y;

	if (width == map->width && height == map->height)
		return (map);
	if ((out = malloc(sizeof(t_map_file) + width * height)) == NULL)
	{
		free(map);
		return (NULL);
	}
	*out = (t_map_file){.magic = W3DM_MAGIC, .height = height, .width = width,
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

static void	click_block(t_glfw_window *win, t_map_file *map, double x, double y)
{
	double			sx;
	double			sy;
	size_t			i;

	sx = (double)win->w_width / (double)map->width;
	sy = (double)win->w_height / (double)map->height;
	i = (size_t)(x / sx) + (size_t)(y / sy) * map->width;
	map->map[i] ^= 1;
}

static void	*click(GLFWwindow *win, int key, int act, int mod)
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
		click_block(u_win, ((t_env*)u_win->user_ptr)->map_file, x, y);
	}
	return (NULL);
}

t_env		*map_editor(t_env *env)
{
	if (env->map_file == NULL && (default_map(env)) == NULL)
		return (NULL);
	if ((env->minimap = glfw_new_window(env->map_file->width * 25,
			env->map_file->height * 25, "map editor", env)) == NULL)
		return (NULL);
	glfwSetMouseButtonCallback(env->minimap->w, (GLFWmousebuttonfun) & click);
	return (env);
}
