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
	out.base_bmp = assets_get_texture(&env->assets, "Button_Base", NULL);
	out.hover_bmp = assets_get_texture(&env->assets, "Button_Hover", NULL);
	out.active_bmp = ft_bmp_default();
	return (out);
}

static inline void		context_main_menu_loop(t_env *env)
{
	while (env->context == W3DC_MAIN_MENU)
	{
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
}

void					context_main_menu_load(t_env *env)
{
	t_gui		gui;
	t_button	buttons[6];
	size_t		i;
	t_bmp	*texture;

	env->context = W3DC_MAIN_MENU;
	gui = gui_gui();
	i = -1;
	while (++i < 6)
	{
		buttons[i] = i_button(560, 100 + 150 * i, env, ((int[6]){
			/*W3DC_NEW_GAME_MENU*/W3DC_PLAYING, W3DC_LOAD_GAME_MENU,
			W3DC_MAP_EDITOR_MENU, W3DC_OPTIONS_MENU, W3DC_CREDITS,
			W3DC_EXIT})[i]);
		gui_attach_button(&gui, &buttons[i]);
	}
	gui_attach_to_window(env->wolf3d, &gui, 0);
	texture = assets_get_texture(&env->assets, "Menu", NULL);
	draw_bmp(env->wolf3d, (t_int2){WOLF3D_DEFAULT_WINDOW_SIZE.x / 2 -
			texture->size.x, 10}, (t_int2){texture->size.x * 2,
			texture->size.y * 2}, texture);
	context_main_menu_loop(env);
}
