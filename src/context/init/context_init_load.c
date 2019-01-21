/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_init_load.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

int	context_init_load(t_env *env)
{
	char *buf;

	set_context(env, W3DC_INIT);
	env->assets = assets_load(WOLF3D_ASSETS_JSON_PATH);
	if ((env->wolf3d = glfw_new_window(WOLF3D_DEFAULT_WINDOW_SIZE.x,
			WOLF3D_DEFAULT_WINDOW_SIZE.y, WOLF3D_DEFAULT_WINDOW_NAME,
			env)) == NULL)
	{
		ft_printf("Could not create window: %s\n", WOLF3D_DEFAULT_WINDOW_NAME);
		return (-1);
	}
	if (load_config(WOLF3D_CONFIG_W3C_PATH, env) == NULL)
		default_config(env);
	printf("test:\n");
	if (get_maps_in_dir("maps", &buf, 1) == 1)
	{
		printf("map: %s\n", buf);
		free(buf);
	}
	set_context(env, W3DC_MAIN_MENU);
	return (0);
}
