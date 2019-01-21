/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_in_game_menu_load.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/01/01 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

static void				i_callback(t_glfw_window *win,
									int status,
									void *data,
									t_button *button)
{
	t_env	*e;
	int		c;

	(void)status;
	(void)button;
	e = (t_env*)win->user_ptr;
	c = (int)(size_t)data;
	if (c == 0)
		save("saves/test.w3ds", e);
	else if (c == 1)
		set_context(e, W3DC_LOAD_GAME_MENU);
	else if (c == 2)
		set_context(e, W3DC_MAIN_MENU);
	else
		set_context(e, W3DC_PLAYING);
}

static inline t_button	i_button(int y, t_env *env, int context, char *text)
{
	t_button	out;

	out = gui_button_click((t_int2){560, y}, (t_int2){200, 40}, i_callback,
		(void*)(size_t)context);
	out.base_bmp = assets_get_texture(&env->assets, "Button_Base", NULL);
	out.hover_bmp = assets_get_texture(&env->assets, "Button_Hover", NULL);
	out.active_bmp = ft_bmp_default();
	pen_set_work_area(env->wolf3d, (t_int2){775, y}, (t_int2){950, y + 60});
	draw_text(env->wolf3d, (t_int2){775, y}, text, 0);
	return (out);
}

static inline void		context_in_game_menu_loop(t_env *env)
{
	while (env->context == W3DC_PLAYING_MENU)
	{
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
}

void	context_in_game_menu_load(t_env *env)
{
	t_gui		gui;
	t_button	buttons[4];
	size_t		i;

	draw_clear(env->wolf3d, 0x880000);
	gui = gui_gui();
	i = -1;
	while (++i < 4)
	{
		buttons[i] = i_button(200 + 150 * i, env, i, ((char*[4]){"Save",
			"Load", "Main Menu", "Continue"})[i]);
		gui_attach_button(&gui, &buttons[i]);
	}
	gui_attach_to_window(env->wolf3d, &gui, 0);
	context_in_game_menu_loop(env);
	gui_destroy(&gui);
}
