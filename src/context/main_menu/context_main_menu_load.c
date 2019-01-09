/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_main_menu_load.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/09 23:39:22 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

static void				i_callback(t_glfw_window *win,
									int status,
									void *data,
									t_button *button)
{
	(void)status;
	(void)button;
	((t_env*)win->user_ptr)->context = (int)(size_t)data;
}

static inline t_button	i_button(int x, int y, t_env *env, int context)
{
	t_button	out;

	out = gui_button_click((t_int2){x, y}, (t_int2){200, 40}, i_callback,
		(void*)(size_t)context);
	if (env->assets.nb_textures > 1)
		out.base_bmp = env->assets.textures[1];
	if (env->assets.nb_textures > 2)
		out.hover_bmp = env->assets.textures[2];
	out.active_bmp = ft_bmp_default();
	return (out);
}

int	context_main_menu_load(t_env *env)
{
	t_gui		gui;
	t_button	new_game;
	t_button	load_game;
	t_button	map_editor;
	t_button	options;
	t_button	credits;
	t_button	exit_game;

	env->context = W3DC_MAIN_MENU;
	gui = gui_gui();
	new_game = i_button(560, 100, env, /*W3DC_NEW_GAME_MENU*/W3DC_PLAYING);
	load_game = i_button(560, 250, env, W3DC_LOAD_GAME_MENU);
	map_editor = i_button(560, 400, env, W3DC_MAP_EDITOR_MENU);
	options = i_button(560, 550, env, W3DC_OPTIONS_MENU);
	credits = i_button(560, 700, env, W3DC_CREDITS);
	exit_game = i_button(560, 850, env, W3DC_EXIT);
	gui_attach_button(&gui, &new_game);
	gui_attach_button(&gui, &load_game);
	gui_attach_button(&gui, &map_editor);
	gui_attach_button(&gui, &options);
	gui_attach_button(&gui, &credits);
	gui_attach_button(&gui, &exit_game);
	gui_attach_to_window(env->wolf3d, &gui, 0);
	return (context_main_menu_loop(env));
}
