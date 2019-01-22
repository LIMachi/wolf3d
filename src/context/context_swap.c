/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/09 23:44:44 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

static inline void	i_clear_callbacks(t_env *env)
{
	if (env->wolf3d != NULL)
	{
		glfwSetKeyCallback(env->wolf3d->w, NULL);
		glfwSetScrollCallback(env->wolf3d->w, NULL);
		glfwSetMouseButtonCallback(env->wolf3d->w, NULL);
		glfwSetCursorPosCallback(env->wolf3d->w, NULL);
		if (env->wolf3d->gui != NULL)
			env->wolf3d->gui = NULL;
	}
	if (env->minimap != NULL)
	{
		glfwSetKeyCallback(env->minimap->w, NULL);
		glfwSetScrollCallback(env->minimap->w, NULL);
		glfwSetMouseButtonCallback(env->minimap->w, NULL);
		glfwSetCursorPosCallback(env->minimap->w, NULL);
		if (env->minimap->gui != NULL)
			env->minimap->gui = NULL;
	}
}

int					set_context(t_env *env, int context)
{
	env->prev_context = env->context;
	env->context = context;
	return (env->prev_context);
}

void				context_swap(t_env *env)
{
	while (env->context != W3DC_EXIT && !glfwWindowShouldClose(env->wolf3d->w))
	{
		i_clear_callbacks(env);
		if (env->context == W3DC_MAIN_MENU)
			context_main_menu_load(env);
		else if (env->context == W3DC_NEW_GAME_MENU)
			context_new_game_menu_load(env);
		else if (env->context == W3DC_PLAYING)
			context_playing_load(env);
		else if (env->context == W3DC_PLAYING_MENU)
			context_in_game_menu_load(env);
		else if (env->context == W3DC_LOAD_GAME_MENU)
			context_load_game_menu_load(env);
		else if (env->context == W3DC_MAP_EDITOR)
			NULL;
		else if (env->context == W3DC_MAP_EDITOR_MENU)
			NULL;
		else if (env->context == W3DC_OPTIONS_MENU)
			context_options_menu_load(env);
		else if (env->context == W3DC_CREDITS)
			NULL;
	}
}
