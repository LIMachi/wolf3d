/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_playing_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:20:37 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/22 10:24:53 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	context_playing_loop(t_env *env)
{
	t_raycast	rc;

	rc.texture = assets_get_texture(&env->assets, "Wall_1", NULL);
	rc.texturen2 = assets_get_texture(&env->assets, "dancefloor", NULL);
	rc.skybox = assets_get_texture(&env->assets, "skybox", NULL);
	while (env->context == W3DC_PLAYING)
	{
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
		if (glfwGetKey(env->wolf3d->w, GLFW_KEY_H))
		{
			set_context(env, W3DC_PLAYING);
			ray_caster(env->player, env, 1, rc);
			minimap(env);
		}
		else
			ray_caster(env->player, env, 1, rc);
		if (glfwGetKey(env->wolf3d->w, GLFW_KEY_ESCAPE))
			set_context(env, W3DC_PLAYING_MENU);
	}
}
