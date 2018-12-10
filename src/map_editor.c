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

void		click_block(t_glfw_window *win, t_map_file *map, double x, double y)
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
		click_block(u_win, ((t_env*)u_win->user_ptr)->map_file, x, y);
	}
	return (NULL);
}


void	*moove_player(GLFWwindow *win, int key, int scan, int act, int mod)
{
	t_glfw_window	*cheat;
	t_env			*env;
	t_vector		vlook;

	(void)scan;
	(void)mod;
	if (act != GLFW_PRESS && act != GLFW_REPEAT)
		return (NULL);
	cheat = glfwGetWindowUserPointer(win);
	env = cheat->user_ptr;
	if (key == env->config_file.backward)
	{
		vlook = rotate_2d((t_vector){0, 0.5}, env->player.look);
		env->player.pos.x += vlook.x;
		env->player.pos.y += vlook.y;
	}
	else if (key == env->config_file.strafe_left)
	{
		vlook = rotate_2d((t_vector){-0.5, 0}, env->player.look);
		env->player.pos.x += vlook.x;
		env->player.pos.y += vlook.y;
	}
	else if (key == env->config_file.strafe_right)
	{
		vlook = rotate_2d((t_vector){0.5, 0}, env->player.look);
		env->player.pos.x += vlook.x;
		env->player.pos.y += vlook.y;
	}
	else if (key == env->config_file.forward)
	{
		vlook = rotate_2d((t_vector){0, -0.5}, env->player.look);
		env->player.pos.x += vlook.x;
		env->player.pos.y += vlook.y;
	}
	else if (key == GLFW_KEY_E)
		env->player.look += 4;
	else if (key == GLFW_KEY_Q)
		env->player.look -= 4;
	return (NULL);
}

t_env	*map_editor(t_env *env)
{
	t_glfw_window	*win;

	if (env->map_file == NULL && (default_map(env)) == NULL)
		return (NULL);
	if ((win = glfw_new_window(env->map_file->width * 25, env->map_file->height * 25,
					"map editor", env)) == NULL)
		return (NULL);
	glfwSetMouseButtonCallback(win->w, (GLFWmousebuttonfun) & click);
	while (!glfwWindowShouldClose(win->w))
	{
		draw_map(win, env);
		glfw_refresh_window(win);
		glfwPollEvents();
		glfwSetKeyCallback(win->w, (GLFWkeyfun)moove_player);
		if (glfwGetKey(win->w, GLFW_KEY_S) == GLFW_PRESS)
			save_map("test.w3d", env->map_file);
	}
	glfw_remove_window(win);
	return (env);
}
