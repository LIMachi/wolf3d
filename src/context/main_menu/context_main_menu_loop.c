/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_main_menu_loop.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

static void	i_draw(t_env *env, t_glfw_window *win)
{
	draw_bmp(win,
		(t_int2){WOLF3D_DEFAULT_WINDOW_SIZE.x / 2 -
			env->assets.textures[3]->size.x, 10},
		(t_int2){env->assets.textures[3]->size.x * 2,
			env->assets.textures[3]->size.y * 2},
		env->assets.textures[3]);
}

int	context_main_menu_loop(t_env *env)
{
	while (env->context == W3DC_MAIN_MENU)
	{
		i_draw(env, env->wolf3d);
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
	return (0);
}
