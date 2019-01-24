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

static void				i_key_callback(GLFWwindow *w,
										int key,
										int scan,
										int act)
{
	(void)w;
	(void)scan;
	if (act == GLFW_RELEASE || key == GLFW_KEY_ESCAPE)
		return ;
}

static void				i_callback(t_glfw_window *win,
	int status,
	void *data,
	t_button *button)
{
	size_t	index;
	t_env	*env;
	size_t	i;

	(void)status;
	(void)button;
	env = (t_env*)win->user_ptr;
	index = (size_t)data;
	i = -1;
	if (index == 6)
		set_context(env, W3DC_MAIN_MENU);
	else if (index == 7)
	{
		env->music_volume = (double)(status - 800) / 100.0;
		if (sound_player()->nb_sounds)
		{
			sound_player()->playing[0].right_gain = env->music_volume;
			sound_player()->playing[0].left_gain = env->music_volume;
		}
	}
	else if (status)
		while (++i < 6)
			((t_button*)env->user_ptr)[i].status = i == index;
}

static inline t_button	i_button(int y, t_env *env, size_t index)
{
	t_button	out;

	out = gui_button_switch((t_int2){560, y}, (t_int2){200, 40},
		i_callback, (void*)index);
	out.base_bmp = assets_get_texture(&env->assets, "Button_Base", NULL);
	out.active_bmp = assets_get_texture(&env->assets, "Button_Hover", NULL);
	out.hover_bmp = index == 6 ? out.active_bmp : out.base_bmp;
	return (out);
}

static inline void		context_options_menu_loop(t_env *env)
{
	size_t	i;
	t_int2	c;

	while (env->context == W3DC_OPTIONS_MENU)
	{
		draw_clear(env->wolf3d, 0x880000);
		i = -1;
		while (++i < 7)
		{
			pen_set_work_area(env->wolf3d, (t_int2){775, 200 + 100 * i},
				(t_int2){1050, 270 + 100 * i});
			c = draw_text(env->wolf3d, (t_int2){775, 200 + 100 * i},
				((char*[7]){"Forward: ", "Backward: ", "Left Strafe: ",
					"Right Strafe: ", "Left Turn: ", "Right Turn: ",
					"Back"})[i], 0);
			if (i != 6)
				draw_text(env->wolf3d, c,
					(char*)glfwGetKeyName(((int32_t*)&env->config_file)[i + 1],
						0), 0);
		}
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
}

void					context_options_menu_load(t_env *env)
{
	t_gui		gui;
	t_button	buttons[8];
	size_t		i;

	gui = gui_gui();
	buttons[7] = gui_button_slider_horizontal((t_int2){360, 100},
		(t_int2){1000, 20}, i_callback, (void*)7);
	buttons[7].base_bmp = assets_get_texture(&env->assets, "Button_Base", NULL);
	buttons[7].hover_bmp = assets_get_texture(&env->assets, "Button_Base",
		NULL);
	buttons[7].active_bmp = assets_get_texture(&env->assets, "Button_Hover",
		NULL);
	gui_attach_button(&gui, &buttons[7]);
	buttons[7].status = env->music_volume * 100 + 800;
	i = -1;
	while (++i < 7)
	{
		buttons[i] = i_button(200 + 100 * i, env, i);
		gui_attach_button(&gui, &buttons[i]);
	}
	env->user_ptr = (void*)buttons;
	gui_attach_to_window(env->wolf3d, &gui, 0);
	glfwSetKeyCallback(env->wolf3d->w, (GLFWkeyfun)i_key_callback);
	context_options_menu_loop(env);
	gui_destroy(&gui);
}
