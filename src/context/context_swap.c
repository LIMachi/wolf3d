/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

int	context_swap(t_env *env)
{
	while (env->context != W3DC_EXIT && !glfwWindowShouldClose(env->wolf3d->w))
		if (env->context == W3DC_MAIN_MENU)
			context_main_menu_load(env);
		else if (env->context == W3DC_NEW_GAME_MENU)
			NULL;
		else if (env->context == W3DC_PLAYING)
			NULL;
		else if (env->context == W3DC_PLAYING_MENU)
			NULL;
		else if (env->context == W3DC_LOAD_GAME_MENU)
			NULL;
		else if (env->context == W3DC_MAP_EDITOR)
			NULL;
		else if (env->context == W3DC_MAP_EDITOR_MENU)
			NULL;
		else if (env->context == W3DC_OPTIONS_MENU)
			NULL;
	return (0);
}
