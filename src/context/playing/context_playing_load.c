/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_playing_load.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:03:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/09 23:22:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	move_player(t_env *env, t_double2 vlook)
{
	t_int2 pos_map;
	t_int2 delta_map;

	pos_map = (t_int2){.x = env->player.pos.x + vlook.x, .y = env->player.pos.y
		+ vlook.y};
	delta_map = (t_int2){.x = pos_map.x - (int)env->player.pos.x,
		.y = pos_map.y - (int)env->player.pos.y};
	if (env->player.pos.x + vlook.x < 0.0)
		env->player.pos.x = 0.01;
	else if (env->player.pos.x + vlook.x >= (double)env->map_file->width - 1)
		env->player.pos.x = (double)env->map_file->width - 1.01;
	else if (delta_map.x && env->map_file->map[pos_map.x + pos_map.y
		* env->map_file->width])
		NULL;
	else
		env->player.pos.x += vlook.x;
	if (env->player.pos.y + vlook.y < 0.0)
		env->player.pos.y = 0.01;
	else if (env->player.pos.y + vlook.y >= (double)env->map_file->height - 1)
		env->player.pos.y = (double)env->map_file->height - 1.01;
	else if (delta_map.y && env->map_file->map[pos_map.x + pos_map.y
		* env->map_file->width])
		NULL;
	else
		env->player.pos.y += vlook.y;
}

void	move_player_callback(GLFWwindow *win, int key, int scan, int act, int mod)
{
	t_glfw_window	*glfw;
	t_env			*env;
	t_double2		vlook;

	(void)scan;
	(void)mod;
	if (act != GLFW_PRESS && act != GLFW_REPEAT)
		return ;
	glfw = glfwGetWindowUserPointer(win);
	env = glfw->user_ptr;
	vlook = (t_double2){.x = 0.0, .y = 0.0};
	if (key == env->config_file.backward)
		vlook = rotate_2d((t_double2){0, 0.1}, env->player.look);
	else if (key == env->config_file.strafe_left)
		vlook = rotate_2d((t_double2){-0.1, 0}, env->player.look);
	else if (key == env->config_file.strafe_right)
		vlook = rotate_2d((t_double2){0.1, 0}, env->player.look);
	else if (key == env->config_file.forward)
		vlook = rotate_2d((t_double2){0, -0.1}, env->player.look);
	else if (key == env->config_file.turn_right)
		env->player.look += 4;
	else if (key == env->config_file.turn_left)
		env->player.look -= 4;
	move_player(env, vlook);
}

void	context_playing_load(t_env *env)
{
	glfwSetKeyCallback(env->wolf3d->w, (GLFWkeyfun)move_player_callback);
	env->context = W3DC_PLAYING;
	context_playing_loop(env);
}
