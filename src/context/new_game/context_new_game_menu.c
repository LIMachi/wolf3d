/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_new_game_menu_load.c                       :+:      :+:    :+:   */
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
	(void)status;
	(void)button;
	if ((size_t)data > 10)
	{
		load_map((char*)data, (t_env*)win->user_ptr);
		set_context((t_env*)win->user_ptr, W3DC_PLAYING);
	}
	else if ((size_t)data == 0)
		set_context((t_env*)win->user_ptr,
			((t_env*)win->user_ptr)->prev_context);
}

static inline t_button	i_button(int y, t_env *env, char *file)
{
	t_button	out;

	out = gui_button_click((t_int2){560, y}, (t_int2){200, 40}, i_callback,
		(void*)file);
	out.base_bmp = assets_get_texture(&env->assets, "Button_Base", NULL);
	out.hover_bmp = assets_get_texture(&env->assets, "Button_Hover", NULL);
	out.active_bmp = ft_bmp_default();
	return (out);
}

static inline void		context_new_game_loop(t_env *env)
{
	int		i;
	int		y;
	char	*text;

	while (env->context == W3DC_NEW_GAME_MENU && (i = -1))
	{
		draw_clear(env->wolf3d, 0x880000);
		while (++i < env->wolf3d->gui->nb_buttons)
		{
			y = env->wolf3d->gui->buttons[i]->pos.y;
			pen_set_work_area(env->wolf3d, (t_int2){775, y},
				(t_int2){1500, y + 100});
			if ((text = (char*)env->wolf3d->gui->buttons[i]->user_data) != NULL)
				if (ft_strrchr(text, '/') != NULL)
					draw_text(env->wolf3d, (t_int2){775, y},
						ft_strrchr(text, '/') + 1, 0);
				else
					draw_text(env->wolf3d, (t_int2){775, y}, text, 0);
			else
				draw_text(env->wolf3d, (t_int2){775, y}, "Back", 0);
		}
		gui_draw(env->wolf3d, env->wolf3d->gui);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
	}
}

static inline void		i_context_new_game_menu_load(t_env *env, size_t *c,
	t_button **buttons, char ***files)
{
	*c = get_maps_in_dir("maps", NULL, -1);
	if ((*files = malloc(sizeof(char *) * *c)) == NULL)
	{
		env->context = W3DC_EXIT;
		return ;
	}
	*c = get_maps_in_dir("maps", *files, *c);
	if ((*buttons = malloc(sizeof(t_button) * (*c + 1))) == NULL)
	{
		env->context = W3DC_EXIT;
		return ;
	}
}

void					context_new_game_menu_load(t_env *env)
{
	t_gui		gui;
	t_button	*buttons;
	size_t		c;
	size_t		i;
	char		**files;

	gui = gui_gui();
	i_context_new_game_menu_load(env, &c, &buttons, &files);
	if (env->context == W3DC_EXIT)
		return ;
	buttons[c] = i_button(100, env, NULL);
	gui_attach_button(&gui, &buttons[c]);
	i = c;
	while (i--)
	{
		buttons[i] = i_button(200 + 150 * i, env, files[i]);
		gui_attach_button(&gui, &buttons[i]);
	}
	gui_attach_to_window(env->wolf3d, &gui, 0);
	context_new_game_loop(env);
	while (c--)
		free(files[c]);
	free(files);
	free(buttons);
	gui_destroy(&gui);
}
