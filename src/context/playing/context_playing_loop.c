/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_playing_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 23:20:37 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/10 20:52:57 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

void	ray_cast(t_env *env, t_double2 pos, t_double2 ray, t_raycast *rc)
{
	int stepx;
	int stepy;
	t_double2	inter;

//	t_double2 ray = rotate_2d((t_double2){.x = 0, .y = -1}, dir);
	int hit = 0;
	double dx = fabs(1 / ray.x);
	double dy = fabs(1 / ray.y);

	rc->mapx = (int)pos.x;
	rc->mapy = (int)pos.y;
	if (ray.x < 0)
	{
		stepx = -1;
		inter.x = (pos.x - rc->mapx) * dx;
	}
	else
	{
		stepx = 1;
		inter.x = (rc->mapx + 1.0 - pos.x) * dx;
	}
	if (ray.y < 0)
	{
		stepy = -1;
		inter.y = (pos.y - rc->mapy) * dy;
	}
	else
	{
		stepy = 1;
		inter.y = (rc->mapy + 1.0 - pos.y) * dy;
	}
	while (hit == 0)
	{
		if (inter.x < inter.y)
		{
			inter.x += dx;
			rc->mapx += stepx;
			rc->face = 0;
		}
		else
		{
			inter.y += dy;
			rc->mapy += stepy;
			rc->face = 1;
		}

		if (rc->mapx < 0 || rc->mapx >= (int)env->map_file->width || rc->mapy < 0 || rc->mapy >= (int)env->map_file->height)
			hit = 1;
		else if (env->map_file->map[rc->mapx + rc->mapy * env->map_file->width] > 0)
			hit = 1;
	}

	if (rc->face == 0)
		rc->dist = (rc->mapx - pos.x + (1 - stepx) / 2) / ray.x;
	else
		rc->dist = (rc->mapy - pos.y + (1 - stepy) / 2) / ray.y;

	if (stepx < 0 && rc->face == 0)
		rc->face = 2;
	if (stepy < 0 && rc->face == 1)
		rc->face = 3;
	//return ((t_double2){.x = pos.x + ray.x * dist, .y = pos.y + ray.y * dist});
	if (rc->face == 0)
		rc->where = pos.y + rc->dist * ray.y;
	if (rc->face == 1)
		rc->where = pos.x + rc->dist * ray.x;
	if (rc->face == 2)
		rc->where = pos.y + rc->dist * ray.y;
	if (rc->face == 3)
		rc->where = pos.x + rc->dist * ray.x;
	rc->where -= (int)rc->where;
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
	t_double2	ray;
	size_t		i;
	t_raycast	rc;

	rc.sizewall = 650;
	t_bmp		*texture;

	texture = assets_get_texture(&e->assets, "Wall_1", NULL);

	if (mc)
		//fov = (double)e->config_file.fov / 100.0;
		rc.fov = 60.0;
	else
		rc.fov = 60.0;
	i = -1;
	while (++i < e->wolf3d->vb_width)
	{
		rc.angle = -rc.fov / 2.0 + rc.fov * (double)i / (double)e->wolf3d->vb_width;
		ray = rotate_2d((t_double2){0, -1}, rc.angle + p.look);
		ray_cast(e, p.pos, ray, &rc);
		if (rc.dist < 0.4)
			rc.dist = 0.4;
		rc.real = rc.dist * cos(DEG_TO_RAD * rc.angle);
		rc.hauteur = (rc.sizewall) / rc.real;
		rc.floor = e->wolf3d->vb_height / 2 + rc.hauteur;
		rc.sky = e->wolf3d->vb_height / 2 - rc.hauteur;
		if (mc)
		{
			int tx;
			int ty;
			tx = (double)texture->size.x * rc.where;
			for (int blurp = 0; blurp < rc.hauteur * 2; ++blurp)
			{
				ty = (double)texture->size.y * (blurp / (rc.hauteur * 2));
				draw_pixel(e->wolf3d, i, e->wolf3d->vb_height / 2 - rc.hauteur + blurp,
					texture->data[tx + ty * texture->size.x]);
			}
			draw_pixel(e->wolf3d, i, rc.floor++, 0);
			draw_pixel(e->wolf3d, i, rc.sky--, 0);
			while (rc.floor <= (int)e->wolf3d->vb_height)
			{
				draw_pixel(e->wolf3d, i, rc.floor++, 0xffffff);
				draw_pixel(e->wolf3d, i, rc.sky--, 0x505050);
			}
		}
	}
}

void	draw(t_env *env, t_glfw_window *win)
{
	ray_caster(env->player, env, 1);
	(void)win;
}

void	context_playing_loop(t_env *env)
{
	while (env->context == W3DC_PLAYING)
	{
		draw(env, env->wolf3d);
		glfw_refresh_window(env->wolf3d);
		glfwPollEvents();
		if (glfwGetKey(env->wolf3d->w, GLFW_KEY_ESCAPE))
			env->context = W3DC_MAIN_MENU;
	}
}
