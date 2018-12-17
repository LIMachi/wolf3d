/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/14 21:38:00 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	char *s;
	(void)win;
	(void)mod;
	printf("(0x%X) %s: %s\n", key, glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	if (key == GLFW_KEY_Q && act == GLFW_PRESS)
		glfwSetWindowShouldClose(win, 1);
	s = (char*)glfwGetKeyName(key, scan);
}

void	center_cursor(GLFWwindow *win)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	glfwSetCursorPos(win, (double)width / 2.0, (double)height / 2.0);
}

void	print_cursor_pos(GLFWwindow *win, double x, double y)
{
	int width;
	int height;

	glfwGetWindowSize(win, &width, &height);
	printf("cursor pos: %.0f%% %.0f%%\n", (x / (double)width - 0.5) * 100.0, (0.5 - y / (double)height) * 100.0);
//	center_cursor(win);
}

void	print_mouse_button(GLFWwindow *win, int key, int act, int mod)
{
	(void)win;
	printf("key: %d, %s, %d\n", key, act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"), mod);
}

void			draw(t_glfw_window *win)
{
	for (int x = 0; x < win->w_width; ++x)
		for (int y = 0; y < win->w_height; ++y)
			*((uint32_t*)&win->vb[(y * win->w_width + x) * 4]) = 0xFF0000;
	if (win->gui != NULL)
		gui_draw(win, win->gui);
	/*
	for (int i = 0; i < win->gui->nb_buttons; ++i)
	{
		t_button *button = win->gui->buttons[i];
		if (button->hover)
			draw_square(win, button->pos, button->size, 0xFF00);
		else
			draw_square(win, button->pos, button->size, 0xFF);
		if (win->gui->buttons[i]->type == BUTTON_TYPE_SLIDER_HORIZONTAL)
			draw_line(win, (t_int2){.x = button->pos.x + button->status, .y = button->pos.y},
				(t_int2){.x = button->pos.x + button->status, .y = button->pos.y + button->size.y},
				0x7777);
		if (win->gui->buttons[i]->type == BUTTON_TYPE_SLIDER_VERTICAL)
			draw_line(win, (t_int2){.y = button->pos.y + button->status, .x = button->pos.x},
				(t_int2){.y = button->pos.y + button->status, .x = button->pos.x + button->size.x},
				0x7777);
	}
	*/
//	t_bmp	*bmp;
//	bmp = bmp_file_load("assets/images/sprites/guard/die/1.bmp");
//	draw_bmp(win, (t_int2){0, 0}, (t_int2){bmp->size.x * 2, bmp->size.y * 2}, bmp);
//	free(bmp);
}

void	resize(GLFWwindow *win, int x, int y)
{
	t_glfw_window	*w;

	w = glfwGetWindowUserPointer(win);
	w->w_height = y;
	w->w_width = x;
	glfw_window_resize_video_buffer(w, x, y);
	draw(w);
}

void	move_player(t_env *env, t_double2 vlook)
{
	t_int2 pos_map;
	t_int2 delta_map;

	pos_map = (t_int2){.x = env->player.pos.x + vlook.x, .y = env->player.pos.y + vlook.y};
	delta_map = (t_int2){.x = pos_map.x - (int)env->player.pos.x,
		.y = pos_map.y - (int)env->player.pos.y};
	if (env->player.pos.x + vlook.x < 0.0)
		env->player.pos.x = 0.01;
	else if (env->player.pos.x + vlook.x >= (double)env->map_file->width - 1)
		env->player.pos.x = (double)env->map_file->width - 1.01;
	else if (delta_map.x && env->map_file->map[pos_map.x + pos_map.y * env->map_file->width])
		NULL;
	else
		env->player.pos.x += vlook.x;
	if (env->player.pos.y + vlook.y < 0.0)
		env->player.pos.y = 0.01;
	else if (env->player.pos.y + vlook.y >= (double)env->map_file->height - 1)
		env->player.pos.y = (double)env->map_file->height - 1.01;
	else if (delta_map.y && env->map_file->map[pos_map.x + pos_map.y * env->map_file->width])
		NULL;
	else
		env->player.pos.y += vlook.y;
}

void	move_player_callback(GLFWwindow *win, int key, int scan, int act, int mod)
{
	t_glfw_window	*glfw;
	t_env			*env;
	t_double2		vlook;

	(void)scan;
	(void)mod;
	if (act != GLFW_PRESS && act != GLFW_REPEAT)
		return ;
	glfw = glfwGetWindowUserPointer(win);
	env = glfw->user_ptr;
	vlook = (t_double2){.x = 0.0, .y = 0.0};
	if (key == env->config_file.backward)
		vlook = rotate_2d((t_double2){0, 0.1}, env->player.look);
	else if (key == env->config_file.strafe_left)
		vlook = rotate_2d((t_double2){-0.1, 0}, env->player.look);
	else if (key == env->config_file.strafe_right)
		vlook = rotate_2d((t_double2){0.1, 0}, env->player.look);
	else if (key == env->config_file.forward)
		vlook = rotate_2d((t_double2){0, -0.1}, env->player.look);
	else if (key == env->config_file.turn_right)
		env->player.look += 4;
	else if (key == env->config_file.turn_left)
		env->player.look -= 4;
	move_player(env, vlook);
}

t_collision	ray_cast(t_env *env, t_double2 pos, t_double2 ray)
{
	int stepx;
	int stepy;
	t_double2	inter;

//	t_double2 ray = rotate_2d((t_double2){.x = 0, .y = -1}, dir);
	int hit = 0;
	double dx = fabs(1 / ray.x);
	double dy = fabs(1 / ray.y);
	t_collision		col;

	col.mapx = (int)pos.x;
	col.mapy = (int)pos.y;
	if (ray.x < 0)
	{
		stepx = -1;
		inter.x = (pos.x - col.mapx) * dx;
	}
	else
	{
		stepx = 1;
		inter.x = (col.mapx + 1.0 - pos.x) * dx;
	}
	if (ray.y < 0)
	{
		stepy = -1;
		inter.y = (pos.y - col.mapy) * dy;
	}
	else
	{
		stepy = 1;
		inter.y = (col.mapy + 1.0 - pos.y) * dy;
	}
	while (hit == 0)
	{
		if (inter.x < inter.y)
		{
			inter.x += dx;
			col.mapx += stepx;
			col.face = 0;
		}
		else
		{
			inter.y += dy;
			col.mapy += stepy;
			col.face = 1;
		}

		if (col.mapx < 0 || col.mapx >= (int)env->map_file->width || col.mapy < 0 || col.mapy >= (int)env->map_file->height)
			hit = 1;
		else if (env->map_file->map[col.mapx + col.mapy * env->map_file->width] > 0)
			hit = 1;
	}

	if (col.face == 0)
		col.dist = (col.mapx - pos.x + (1 - stepx) / 2) / ray.x;
	else
		col.dist = (col.mapy - pos.y + (1 - stepy) / 2) / ray.y;

	if (stepx < 0 && col.face == 0)
		col.face = 2;
	if (stepy < 0 && col.face == 1)
		col.face = 3;
	//return ((t_double2){.x = pos.x + ray.x * dist, .y = pos.y + ray.y * dist});
	if (col.face == 0)
		col.where = pos.y + col.dist * ray.y;
	if (col.face == 1)
		col.where = pos.x + col.dist * ray.x;
	if (col.face == 2)
		col.where = pos.y - col.dist * ray.y;
	if (col.face == 3)
		col.where = pos.x - col.dist * ray.x;
	col.where -= (int)col.where;
	return (col);
}

/*
** formule: look - fov / 2.0 + fov * (i / x)
*/

t_int2	vecftoveci(t_double2 v, double sx, double sy)
{
	return ((t_int2){.x = (int)(v.x * sx), .y = (int)(v.y * sy)});
}

t_double2	vecfscale(t_double2 v, double s)
{
	return ((t_double2){.x = v.x * s, .y = v.y * s});
}

t_double2	vecfadd(t_double2 v1, t_double2 v2)
{
	return ((t_double2){.x = v1.x + v2.x, .y = v1.y + v2.y});
}

void	ray_caster(t_player p, t_env *e, int mc)
{
	double		fov;
	t_double2	ray;
	size_t		i;
	t_collision	df;
	int			sizewall = 650;
	double		hauteur;
	double		cheat;
	double		real;

	double sx;
	double sy;

	t_bmp	*bmp = bmp_file_load("assets/images/sprites/ss/SPR_SS_PAIN_2");

	sx = (double)e->minimap->vb_width / (double)e->map_file->width;
	sy = (double)e->minimap->vb_height / (double)e->map_file->height;

	if (mc)
		fov = (double)e->config_file.fov / 100.0;
	else
		fov = 60.0;
	i = -1;
	while (++i < e->wolf3d->vb_width)
	{
		/*collision = ray_cast(e, p.pos,
			p.look - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width);*/
		cheat = - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width;
		ray = rotate_2d((t_double2){0, -1}, cheat + p.look);
		df = ray_cast(e, p.pos, ray);
		draw_line(e->minimap, vecftoveci(p.pos, sx, sy), vecftoveci(vecfadd(p.pos, vecfscale(ray, df.dist)), sx, sy), 0xFFFF00);
		if (df.dist < 0.4)
			df.dist = 0.4;
		real = df.dist * cos(DEG_TO_RAD * cheat);
		hauteur = (sizewall) / real;
		if (mc)
		{
			//if (df.face == 1)
//			{
//				draw_line(e->wolf3d, (t_int2){.x = i, .y = e->wolf3d->vb_height / 2 + hauteur},
//					(t_int2){.x = i, .y = e->wolf3d->vb_height / 2 - hauteur}, 0x0000ff);
//			}
//			printf("df.where: %f\n", df.where);

			if (df.face == 0)
			{
				int tx;
				int ty;
				tx = (double)bmp->size.x * df.where;
//				printf("tx: %d\n", tx);
				for (int blurp = 0; blurp < hauteur * 2; ++blurp)
				{
					ty = (double)bmp->size.y * (blurp / (hauteur * 2));
					draw_pixel(e->wolf3d, i, e->wolf3d->vb_height / 2 - hauteur + blurp, bmp->data[tx + ty * bmp->size.x]);
				}
				//draw_line(e->wolf3d, (t_int2){.x = i, .y = e->wolf3d->vb_height / 2 + hauteur},
				//	(t_int2){.x = i, .y = e->wolf3d->vb_height / 2 - hauteur}, text[tx + ty * 16]);
			}
			else
				draw_line(e->wolf3d, (t_int2){.x = i, .y = e->wolf3d->vb_height / 2 + hauteur},
					(t_int2){.x = i, .y = e->wolf3d->vb_height / 2 - hauteur}, (int[4]){0x0000ff, 0x00ff00, 0x00ffff, 0x777777}[df.face]);
			//	draw_line(e->wolf3d, (t_int2){.x = i, .y = e->wolf3d->vb_height / 2 + hauteur},
			//		(t_int2){.x = i, .y = e->wolf3d->vb_height / 2 - hauteur}, (0x0000ff / 2));
					}
	}
	free(bmp);
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

/*
** t_sound are treated as being const and should not be modified
*/

typedef struct		s_sound
{
	float			*data;
	unsigned int	channels;
	unsigned int	sampleRate;
	drwav_uint64	totalSampleCount;
}					t_sound;

#define MAXIMUM_SOUND_SUPERPOSITION 10

typedef enum		e_sound_flags
{
	SOUND_NONE,
	SOUND_LOOP,
	SOUND_PLAY_ONCE
}					t_sound_flags;

typedef struct		s_sound_playing
{
	t_sound_flags	flags;
	float			left_gain;
	float			right_gain;
	drwav_uint64	left_phase;
	drwav_uint64	right_phase;
	unsigned int	currentSample;
}					t_sound_playing;

typedef struct		s_sound_player
{
	int				nb_sounds;
	t_sound			*sound[MAXIMUM_SOUND_SUPERPOSITION];
	t_sound_playing	playing[MAXIMUM_SOUND_SUPERPOSITION];
}					t_sound_player;

//gain equation -> g = 10 log10(out / int)
//g / 10 = log10(out / in)
//10 ^ (g / 10) = out / in
//for log10:
//out = in * pow(10, (g / 10))
//for log2:
//out = in * pow(2, (g / 10))

int paudioCallback(const void *input,
					void *output,
					unsigned long fpb,
					const PaStreamCallbackTimeInfo *ti,
					PaStreamCallbackFlags flags,
					void *user_ptr)
{
	t_sound_player	*player;
	float			*out;
	unsigned long	i;
	unsigned long	j;

	(void)ti; /* Prevent unused variable warnings. */
	(void)flags;
	(void)input;
	out = (float*)output;
	player = (t_sound_player*)user_ptr;
	for(i = 0; i < fpb; ++i)
	{
		out[0] = 0;
		out[1] = 0;
		for (j = 0; (int)j < player->nb_sounds; ++j)
		{
			if (player->playing[j].currentSample * player->sound[j]->channels >= player->sound[j]->totalSampleCount)
			{
				player->playing[j].currentSample = 0;
				if (player->playing[j].flags == SOUND_PLAY_ONCE)
					player->playing[j].flags = SOUND_NONE;
			}
			if (player->playing[j].flags == SOUND_NONE)
				break ;
			out[0] += pow(10.0, player->playing[j].left_gain / 10.0) * player->sound[j]->data[player->playing[j].left_phase + player->playing[j].currentSample * player->sound[j]->channels];
			out[1] += pow(10.0, player->playing[j].right_gain / 10.0) * player->sound[j]->data[player->playing[j].right_phase + player->playing[j].currentSample * player->sound[j]->channels];
			++player->playing[j].currentSample;
		}
		out += 2;
	}
	j = 0;
	for(i = 0; (int)i < player->nb_sounds; ++i)
		if (player->playing[i].flags != SOUND_NONE)
			player->playing[j++] = player->playing[i];
	player->nb_sounds = (int)j;
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

void clicked(t_glfw_window *win, int status, void *data, t_button *button)
{
	(void)win;
	(void)data;
	printf("button updated: index: %d, status: %d\n", button->index, status);
}

void hover(t_glfw_window *win, int status, void *data, t_button *button)
{
	(void)win;
	(void)data;
	(void)status;
	printf("hover updated: index: %d\n", button->index);
}

int	main(void)
{
	t_env			env;
	int tick = 0;
	int second = (int)time(NULL);

	//
	PaStream		*stream;
	t_sound			sound1;
	t_sound			sound2;
	t_sound_player	player;

	if (paNoError != Pa_Initialize())
		return (0 & printf("can't load portaudio\n"));
	PaStreamParameters outputParameters;
	outputParameters.device = Pa_GetDefaultOutputDevice();
	if (outputParameters.device == paNoDevice)
		return (0 & printf("no valid sound device found\n"));
	outputParameters.channelCount = 2;       /* stereo output */
	outputParameters.sampleFormat = paFloat32; /* 32 bit floating int2 output */
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;
//	sin_wave(2.0, &data);
	sound1.data = drwav_open_and_read_file_f32("assets/sounds/Hydra - Lava Reef Zone (Hydra Remix).wav", &sound1.channels, &sound1.sampleRate, &sound1.totalSampleCount);
	printf("loadded song, channels: %u, sr: %u, total: %llu\n", sound1.channels, sound1.sampleRate, sound1.totalSampleCount);
	sound2.data = drwav_open_and_read_file_f32("assets/sounds/LRMonoPhase4test.wav", &sound2.channels, &sound2.sampleRate, &sound2.totalSampleCount);
	printf("loadded song, channels: %u, sr: %u, total: %llu\n", sound2.channels, sound2.sampleRate, sound2.totalSampleCount);
	player = (t_sound_player){.nb_sounds = 0, .playing = {
		{.flags = SOUND_PLAY_ONCE, .currentSample = 0, .right_gain = 0, .left_gain = 0, .left_phase = 0, .right_phase = sound1.channels > 1},
		{.flags = SOUND_LOOP, .currentSample = 0, .right_gain = 0, .left_gain = 0, .left_phase = 0, .right_phase = sound2.channels > 1}},
		.sound = {&sound1, &sound2}};
	if (sound1.data == NULL || sound2.data == NULL)
		return (0 & printf("can't read audio file\n"));
	Pa_OpenStream(&stream, NULL, &outputParameters, 44100, 0, paClipOff, paudioCallback, &player);
	Pa_SetStreamFinishedCallback(stream, StreamFinished);
	Pa_StartStream(stream);
	//

	if ((env.wolf3d = glfw_new_window(SX, SY, "Wolf3d", &env)) == NULL)
		return (-42);
	env.map_file = NULL;
	if (NULL == load_config("config.w3c", &env))
		default_config(&env);
	glfwSetKeyCallback(env.wolf3d->w, (GLFWkeyfun)print_key);
	glfwSetKeyCallback(env.wolf3d->w, (GLFWkeyfun)move_player_callback);
	env.wolf3d->key_cb = move_player_callback;
	glfwSetMouseButtonCallback(env.wolf3d->w, (GLFWmousebuttonfun)print_mouse_button);
	env.wolf3d->button_cb = print_mouse_button;
	glfwSetCursorPosCallback(env.wolf3d->w, (GLFWcursorposfun)print_cursor_pos);
	env.wolf3d->pos_cb = print_cursor_pos;
	env.wolf3d->scroll_cb = (GLFWscrollfun)noop;
	glfwSetFramebufferSizeCallback(env.wolf3d->w, (GLFWframebuffersizefun)resize);
	map_editor(&env);
	glfwSetKeyCallback(env.minimap->w, (GLFWkeyfun)move_player_callback);
	t_int2 pos;
	glfwGetWindowPos(env.wolf3d->w, &pos.x, &pos.y);
	glfwSetWindowPos(env.minimap->w, pos.x + env.wolf3d->w_width, pos.y);
	glfwFocusWindow(env.wolf3d->w);

	//
	t_button	test_button1 = gui_button_click((t_int2){0, 0}, (t_int2){100, 100}, clicked, NULL);
	t_button	test_button2 = gui_button_switch((t_int2){100, 100}, (t_int2){100, 100}, clicked, NULL);
	t_button	test_button3 = gui_button_slider_horizontal((t_int2){200, 0}, (t_int2){100, 20}, clicked, NULL);
	test_button1.hover_cb = hover;
	test_button2.hover_cb = hover;
	test_button2.active_bmp = bmp_file_load("assets/images/C_HARDPIC");
	test_button3.active_bmp = test_button2.hover_bmp = bmp_file_load("assets/images/C_NORMALPIC");
	test_button2.base_bmp = bmp_file_load("assets/images/C_EASYPIC");
	test_button3.hover_cb = hover;
	test_button3.base_bmp = test_button3.hover_bmp = bmp_file_load("assets/images/H_TOPWINDOWPIC");
	t_gui		test_gui = gui_gui();
	gui_attach_button(&test_gui, &test_button1);
	gui_attach_button(&test_gui, &test_button2);
	gui_attach_button(&test_gui, &test_button3);
	gui_attach_to_window(env.wolf3d, &test_gui);
	//

	while (!glfwWindowShouldClose(env.wolf3d->w))
	{
		draw(env.wolf3d);
		draw_map(env.minimap, &env);
		ray_caster(env.player, &env, 1);
		glfw_refresh_window(env.minimap);
		glfw_refresh_window(env.wolf3d);
		glfwPollEvents();
		if (glfwGetKey(env.wolf3d->w, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(env.wolf3d->w, 1);
		if (glfwGetKey(env.wolf3d->w, GLFW_KEY_KP_SUBTRACT))
		{
			player.playing[0].left_gain -= 0.1;
			player.playing[0].right_gain -= 0.1;
			printf("gain: %f\n", player.playing[0].left_gain);
		}
		if (glfwGetKey(env.wolf3d->w, GLFW_KEY_KP_ADD))
		{
			player.playing[0].left_gain += 0.1;
			player.playing[0].right_gain += 0.1;
			printf("gain: %f\n", player.playing[0].left_gain);
		}
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
	drwav_free(sound1.data);
	drwav_free(sound2.data);
	save_config("config.w3c", &env.config_file);
	return (0);
}
