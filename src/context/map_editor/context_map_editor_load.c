/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_map_editor_load.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/10 16:16:11 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void			click_block(t_glfw_window *win, t_map_file *map, double x,
								double y)
{
	double			sx;
	double			sy;
	size_t			i;

	sx = (double)win->w_width / (double)map->width;
	sy = (double)win->w_height / (double)map->height;
	i = (size_t)(x / sx) + (size_t)(y / sy) * map->width;
	map->map[i] ^= 1;
}

static void			click(GLFWwindow *win, int key, int act, int mod)
{
	double			x;
	double			y;
	t_map_file		*map;
	t_glfw_window	*u_win;

	(void)mod;
	u_win = glfwGetWindowUserPointer(win);
	glfwGetWindowSize(win, &u_win->w_width, &u_win->w_height);
	glfwGetCursorPos(win, &x, &y);
	map = ((t_env*)u_win->user_ptr)->map_file;
	if (x < 0.0 || y < 0.0 || x > (double)u_win->w_width
		|| y > (double)u_win->w_height)
		return ;
	if (key == GLFW_MOUSE_BUTTON_1 && act == GLFW_PRESS)
		click_block(u_win, map, x, y);
	if (key == GLFW_MOUSE_BUTTON_2 && act == GLFW_PRESS)
	{
		map->startx = x / ((double)u_win->w_width / (double)map->width);
		map->starty = y / ((double)u_win->w_height / (double)map->height);
		((t_env*)u_win->user_ptr)->player.pos = (t_double2){map->startx + 0.5,
			map->starty + 0.5};
	}
}

static t_map_file	*map_scale(t_map_file *map, uint32_t width, uint32_t height)
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

static void			key(GLFWwindow *win, int key, int scancode, int action)
{
	t_env		*e;
	t_map_file	*t;

	(void)scancode;
	if (action == GLFW_RELEASE)
		return ;
	e = (t_env*)((t_glfw_window*)glfwGetWindowUserPointer(win))->user_ptr;
	t = e->map_file;
	if (key == GLFW_KEY_KP_ADD)
	{
		if (glfwGetKey(win, GLFW_KEY_Y) && t->height < 42)
			e->map_file = map_scale(t, t->width, t->height + 1);
		else if (glfwGetKey(win, GLFW_KEY_X) && t->width < 42)
			e->map_file = map_scale(t, t->width + 1, t->height);
	}
	else if (key == GLFW_KEY_KP_SUBTRACT)
	{
		if (glfwGetKey(win, GLFW_KEY_Y) && t->height > 3)
			e->map_file = map_scale(t, t->width, t->height - 1);
		else if (glfwGetKey(win, GLFW_KEY_X) && e->map_file->width > 3)
			e->map_file = map_scale(t, t->width - 1, t->height);
	}
	if (t != e->map_file)
		set_context(e, W3DC_RELOAD);
}

void				context_map_editor_load(t_env *env)
{
	if (env->map_file == NULL && (default_map(env)) == NULL)
		return ;
	if ((env->minimap = glfw_new_window(env->map_file->width * 25,
		env->map_file->height * 25, "map editor", env)) == NULL)
		return ;
	glfwSetMouseButtonCallback(env->minimap->w, click);
	glfwSetKeyCallback(env->minimap->w, (GLFWkeyfun)key);
	context_map_editor_loop(env);
	glfw_remove_window(env->minimap);
}
