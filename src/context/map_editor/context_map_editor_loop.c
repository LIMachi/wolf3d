/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_map_editor_loop.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/10 16:16:11 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <time.h>

static char				*i_save_name(void)
{
	static char	name[PATH_MAX];
	time_t		t;

	ft_strcpy(name, "maps/Map_");
	time(&t);
	ft_strcpy(&name[9], ctime(&t));
	name[12] = '_';
	name[16] = '_';
	name[19] = '_';
	name[22] = '_';
	name[25] = '_';
	name[28] = '_';
	ft_strcpy(&name[33], ".w3dm");
	name[39] = '\0';
	return (name);
}

void					context_map_editor_loop(t_env *env)
{
	while (env->context == W3DC_MAP_EDITOR)
	{
		draw_clear(env->minimap, 0xFFFFFF);
		minimap(env, env->minimap, 1.0);
		glfw_refresh_window(env->minimap);
		glfwPollEvents();
		if (glfwGetKey(env->minimap->w, GLFW_KEY_ESCAPE))
			set_context(env, W3DC_MAIN_MENU);
		if (glfwGetKey(env->minimap->w, GLFW_KEY_S) &&
				glfwGetKey(env->minimap->w, GLFW_KEY_LEFT_CONTROL))
			save_map(i_save_name(), env->map_file);
	}
}
