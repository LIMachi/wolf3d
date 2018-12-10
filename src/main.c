/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/10 19:04:59 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	*print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	char *s;
	(void)win;
	(void)mod;
	printf("(0x%X) %s: %s\n", key, glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	if (key == GLFW_KEY_Q && act == GLFW_PRESS)
		glfwSetWindowShouldClose(win, 1);
	s = (char*)glfwGetKeyName(key, scan);
	return (NULL);
}

void	center_cursor(GLFWwindow *win)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	glfwSetCursorPos(win, (double)width / 2.0, (double)height / 2.0);
}

void	*print_cursor_pos(GLFWwindow *win, double x, double y)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	printf("cursor pos: %.0f%% %.0f%%\n", (x / (double)width - 0.5) * 100.0, (0.5 - y / (double)height) * 100.0);
//	center_cursor(win);
	return (NULL);
}

void	*print_mouse_button(GLFWwindow *win, int key, int act, int mod)
{
	(void)win;
	printf("key: %d, %s, %d\n", key, act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"), mod);
	return (NULL);
}

void			draw(t_glfw_window *win)
{
	for (int x = 0; x < win->w_width; ++x)
		for (int y = 0; y < win->w_height; ++y)
			*((uint32_t*)&win->vb[(y * win->w_width + x) * 4]) = 0xFF0000;
//	t_bmp	*bmp;
//	bmp = bmp_file_load("assets/images/sprites/guard/die/1.bmp");
//	draw_bmp(win, (t_vec){0, 0}, (t_vec){bmp->size.x * 2, bmp->size.y * 2}, bmp);
//	free(bmp);
}

void	*resize(GLFWwindow *win, int x, int y)
{
	t_glfw_window	*w;

	w = glfwGetWindowUserPointer(win);
	w->w_height = y;
	w->w_width = x;
	glfw_window_resize_video_buffer(w, x, y);
	draw(w);
	return (w);
}

void	*moove_player(GLFWwindow *win, int key, int scan, int act, int mod)
{
	t_glfw_window	*cheat;
	t_env			*env;
	t_vector		vlook;

	(void)scan;
	(void)mod;
	if (act != GLFW_PRESS && act != GLFW_REPEAT)
		return (NULL);
	cheat = glfwGetWindowUserPointer(win);
	env = cheat->user_ptr;
	vlook = (t_vector){.x = 0.0, .y = 0.0};
	if (key == env->config_file.backward)
		vlook = rotate_2d((t_vector){0, 0.5}, env->player.look);
	else if (key == env->config_file.strafe_left)
		vlook = rotate_2d((t_vector){-0.5, 0}, env->player.look);
	else if (key == env->config_file.strafe_right)
		vlook = rotate_2d((t_vector){0.5, 0}, env->player.look);
	else if (key == env->config_file.forward)
		vlook = rotate_2d((t_vector){0, -0.5}, env->player.look);
	else if (key == env->config_file.turn_right)
		env->player.look += 4;
	else if (key == env->config_file.turn_left)
		env->player.look -= 4;
	env->player.pos.x += vlook.x;
	env->player.pos.y += vlook.y;
	return (NULL);
}

t_vector	ray_cast(t_env *env, t_vector pos, double dir)
{
	double xa;
	double ya;

	ya = 1.0 / tan(dir);
	xa = tan(dir);   //pck ya vaut 1

	if (xa < ya)
	{
		pos
	}
	else
	{
	
	}
}

/*
** formule: look - fov / 2.0 + fov * (i / x)
*/

void	ray_caster(t_player p, t_env *e, int mc)
{
	double		fov;
	t_vector	collision;
	int			i;

	if (mc)
		fov = (double)e->config_file.fov / 100.0;
	else
		fov = 90.0;
	i = -1;
	while (++i < e->wolf3d->vb_width)
	{
		collision = ray_cast(e, p.pos,
			p.look - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width);
	}
}

int	main(void)
{
	t_env			env;
	int tick = 0;
	int second = (int)time(NULL);

	if ((env.wolf3d = glfw_new_window(SX, SY, "Wolf3d", &env)) == NULL)
		return (-42);
	env.map_file = NULL;
	if (NULL == load_config("config.w3c", &env))
		default_config(&env);
	glfwSetKeyCallback(env.wolf3d->w, (GLFWkeyfun)print_key);
	glfwSetKeyCallback(env.wolf3d->w, (GLFWkeyfun)moove_player);
	glfwSetMouseButtonCallback(env.wolf3d->w, (GLFWmousebuttonfun)print_mouse_button);
	glfwSetCursorPosCallback(env.wolf3d->w, (GLFWcursorposfun)print_cursor_pos);
	glfwSetFramebufferSizeCallback(env.wolf3d->w, (GLFWframebuffersizefun)resize);
	map_editor(&env);
	glfwFocusWindow(env.wolf3d->w);
	while (!glfwWindowShouldClose(env.wolf3d->w))
	{
		draw(env.wolf3d);
		glfw_refresh_window(env.wolf3d);
		draw_map(env.minimap, &env);
		glfw_refresh_window(env.minimap);
		glfwPollEvents();
		if (glfwGetKey(env.wolf3d->w, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(env.wolf3d->w, 1);
		if (second != (int)time(NULL))
		{
			second = (int)time(NULL);
			printf("fps: %d\n", tick);
			tick = 0;
		}
		++tick;
	}
	glfwTerminate();
	save_config("config.w3c", &env.config_file);
	return (0);
}
