/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/12 15:09:13 by lmunoz-q         ###   ########.fr       */
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
	int stepx;
	int stepy;
	int side;
	t_vector	inter;

	t_vector ray = rotate_2d((t_vector){.x = 0, .y = -1}, dir);
	int mapX = (int)pos.x;
	int mapY = (int)pos.y;
	int hit = 0;
	double dx = fabs(1 / ray.x);
	double dy = fabs(1 / ray.y);
	double dist;

	if (ray.x < 0)
	{
		stepx = -1;
		inter.x = (pos.x - mapX) * dx;
	}
	else
	{
		stepx = 1;
		inter.x = (mapX + 1.0 - pos.x) * dx;
	}
	if (ray.y < 0)
	{
		stepy = -1;
		inter.y = (pos.y - mapY) * dy;
	}
	else
	{
		stepy = 1;
		inter.y = (mapY + 1.0 - pos.y) * dy;
	}
	while (hit == 0)
	{
		if (inter.x < inter.y)
		{
			inter.x += dx;
			mapX += stepx;
			side = 0;
		}
		else
		{
			inter.y += dy;
			mapY += stepy;
			side = 1;
		}

		if (env->map_file->map[mapX + mapY * env->map_file->width] > 0)
			hit = 1;

	}

	printf("inter.x : %f\ninter.y : %f\n", inter.x, inter.y);
	if (side == 0)
		dist = (mapX - pos.x + (1 - stepx) / 2) / ray.x;
	else
		dist = (mapY - pos.y + (1 - stepy) / 2) / ray.y;
	return ((t_vector){.x = pos.x + ray.x * dist, .y = pos.y + ray.y * dist});
}

/*
** formule: look - fov / 2.0 + fov * (i / x)
*/

t_vec	vecftoveci(t_vector v, double sx, double sy)
{
	return ((t_vec){.x = (int)(v.x * sx), .y = (int)(v.y * sy)});
}

void	ray_caster(t_player p, t_env *e, int mc)
{
	double		fov;
	t_vector	collision;
	size_t			i;

	double sx;
	double sy;

	sx = (double)e->minimap->vb_width / (double)e->map_file->width;
	sy = (double)e->minimap->vb_height / (double)e->map_file->height;
	if (mc)
		fov = (double)e->config_file.fov / 100.0;
	else
		fov = 90.0;
	i = -1;
	while (++i < e->wolf3d->vb_width)
	{
		/*collision = ray_cast(e, p.pos,
			p.look - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width);*/
		collision = ray_cast(e, p.pos,
			p.look - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width);
		draw_line(e->minimap, vecftoveci(p.pos, sx, sy), vecftoveci(collision, sx, sy), 0xFFFF00);
	}
}

#define TABLE_SIZE   (1000)
typedef struct
{
//	float sine[TABLE_SIZE];
	float *data;
	unsigned int channels;
	unsigned int sampleRate;
	unsigned int currentSample;
	drwav_uint64 totalSampleCount;
	drwav_uint64 left_phase;
	drwav_uint64 right_phase;
} paTestData;

int paudioCallback(const void *input,
					void *output,
					unsigned long fpb,
					const PaStreamCallbackTimeInfo *ti,
					PaStreamCallbackFlags flags,
					void *user_ptr)
{
	paTestData *test = (paTestData*)user_ptr;
	float *out = (float*)output;
	unsigned long i;

	(void)ti; /* Prevent unused variable warnings. */
	(void)flags;
	(void)input;
	for(i = 0; i < fpb; ++i)
	{
		if (test->currentSample * test->channels >= test->totalSampleCount)
			return paComplete;
		*out++ = test->data[test->left_phase + test->currentSample * test->channels];
		*out++ = test->data[test->right_phase + test->currentSample * test->channels];
		++test->currentSample;
	}
	return (paContinue);
}

void StreamFinished( void* userData )
{
	(void)userData;
	printf( "Stream Completed\n");
}

/*
void sin_wave(double factor, paTestData *data)
{
	if (factor < 0)
		factor = -factor;
	while (factor > 10.0)
		factor -= 10.0;
	data->local_size = (int)(100.0 * factor);
	for(int i=0; i<data->local_size; i++ )
	{
		data->sine[i] = (float) sin( ((double)i/(double)200) * M_PI * factor );
	}
}
*/

int	main(void)
{
	t_env			env;
	int tick = 0;
	int second = (int)time(NULL);

	//
	PaStream *stream;
	paTestData	data;
	data.left_phase = data.right_phase = 0;
	if (paNoError != Pa_Initialize())
		return (0 & printf("can't load portaudio\n"));
	PaStreamParameters outputParameters;
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice)
		return (0 & printf("no valid sound device found\n"));
	outputParameters.channelCount = 2;       /* stereo output */
	outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
//	sin_wave(2.0, &data);
	data.data = drwav_open_and_read_file_f32("assets/sounds/Hydra - Lava Reef Zone (Hydra Remix).wav", &data.channels, &data.sampleRate, &data.totalSampleCount);
	printf("loadded song, channels: %u, sr: %u, total: %llu\n", data.channels, data.sampleRate, data.totalSampleCount);
	data.left_phase = 0;
	data.right_phase = data.channels > 1;
	data.currentSample = 0;
	if (data.data == NULL)
		return (0 & printf("can't read audio file\n"));
	Pa_OpenStream(&stream, NULL, &outputParameters, data.sampleRate, 0, paClipOff, paudioCallback, &data);
	Pa_SetStreamFinishedCallback(stream, StreamFinished);
	Pa_StartStream(stream);
	//

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
		ray_caster(env.player, &env, 1);
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
	Pa_StopStream(stream);
	Pa_CloseStream(stream);
	Pa_Terminate();
	drwav_free(data.data);
	save_config("config.w3c", &env.config_file);
	return (0);
}
