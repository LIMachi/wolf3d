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

static void	context_map_editor_loop(t_env *env)
{
	while (env->context == W3DC_MAP_EDITOR)
	{
		draw_clear(env->minimap, 0xFFFFFF);
		minimap(env, env->minimap, 1.0);
		glfw_refresh_window(env->minimap);
		glfwPollEvents();
		if (glfwGetKey(env->minimap->w, GLFW_KEY_ESCAPE))
			set_context(env, W3DC_MAIN_MENU);
	}
}

void	context_map_editor_load(t_env *env)
{
	if (env->map_file == NULL && (default_map(env)) == NULL)
		return ;
	if ((env->minimap = glfw_new_window(env->map_file->width * 25,
		env->map_file->height * 25, "map editor", env)) == NULL)
		return ;
	glfwSetMouseButtonCallback(env->minimap->w, (GLFWmousebuttonfun) & click);
	context_map_editor_loop(env);
	glfw_remove_window(env->minimap);
}
