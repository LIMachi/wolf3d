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

static void	i_draw(t_glfw_window *win, t_bmp *texture)
{
	draw_bmp(win,
		(t_int2){WOLF3D_DEFAULT_WINDOW_SIZE.x / 2 -
			texture->size.x, 10},
		(t_int2){texture->size.x * 2,
			texture->size.y * 2},
		texture);
}

int	context_main_menu_loop(t_env *env)
{
	t_bmp	*texture;

	texture = assets_get_texture(&env->assets, "Menu", NULL);
	while (env->context == W3DC_MAIN_MENU)
	{
		i_draw(env->wolf3d, texture);
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
	return (0);
}
