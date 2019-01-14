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

static inline void	init_ray(t_raycast *rc, t_double2 *ray, t_double2 *pos)
{
	rc->dx = fabs(1 / ray->x);
	rc->dy = fabs(1 / ray->y);
	rc->mapx = (int)pos->x;
	rc->mapy = (int)pos->y;
	rc->hit = 0;
	if (ray->x < 0)
	{
		rc->stepx = -1;
		rc->firsthit.x = (pos->x - rc->mapx) * rc->dx;
	}
	else
	{
		rc->stepx = 1;
		rc->firsthit.x = (rc->mapx + 1.0 - pos->x) * rc->dx;
	}
	if (ray->y < 0)
	{
		rc->stepy = -1;
		rc->firsthit.y = (pos->y - rc->mapy) * rc->dy;
	}
	else
	{
		rc->stepy = 1;
		rc->firsthit.y = (rc->mapy + 1.0 - pos->y) * rc->dy;
	}
}

static inline void	i_dda(t_env *env, t_raycast *rc, t_double2 *pos, t_double2 *ray)
{
	if (rc->stepx < 0 && rc->face == 0)
		rc->face = 2;
	if (rc->stepy < 0 && rc->face == 1)
		rc->face = 3;
	//return ((t_double2){.x = pos.x + ray.x * dist, .y = pos.y + ray.y * dist});
	if (rc->face == 0)
		rc->where = pos->y + rc->dist * ray->y;
	if (rc->face == 1)
		rc->where = pos->x + rc->dist * ray->x;
	if (rc->face == 2)
		rc->where = pos->y + rc->dist * ray->y;
	if (rc->face == 3)
		rc->where = pos->x + rc->dist * ray->x;
	rc->real = rc->dist * cos(DEG_TO_RAD * rc->angle);
	rc->hauteur = rc->sizewall / rc->real;
	rc->where -= (int)rc->where;
	rc->floor = env->wolf3d->vb_height / 2 + rc->hauteur;
	rc->sky = env->wolf3d->vb_height / 2 - rc->hauteur;
}

void	dda(t_env *env, t_double2 pos, t_double2 ray, t_raycast *rc)
{
	init_ray(rc, &ray, &pos);
	while (rc->hit == 0)
	{
		if (rc->firsthit.x < rc->firsthit.y)
		{
			rc->firsthit.x += rc->dx;
			rc->mapx += rc->stepx;
			rc->face = 0;
		}
		else
		{
			rc->firsthit.y += rc->dy;
			rc->mapy += rc->stepy;
			rc->face = 1;
		}
		if (rc->mapx < 0 || rc->mapx >= (int)env->map_file->width || rc->mapy < 0 || rc->mapy >= (int)env->map_file->height)
			rc->hit = 1;
		else if (env->map_file->map[rc->mapx + rc->mapy * env->map_file->width] > 0)
			rc->hit = 1;
	}
	if (rc->face == 0)
		rc->dist = (rc->mapx - pos.x + (1.0 - rc->stepx) / 2.0) / ray.x;
	else
		rc->dist = (rc->mapy - pos.y + (1.0 - rc->stepy) / 2.0) / ray.y;
	i_dda(env, rc, &pos, &ray);
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

void	draw_wolf(t_env *e, t_player p, t_raycast *rc, size_t i)
{
	t_double2	ray;

	rc->angle = -rc->fov / 2.0 + rc->fov * (double)i / (double)e->wolf3d->vb_width;
	ray = rotate_2d((t_double2){0, -1}, rc->angle + p.look);
	dda(e, p.pos, ray, rc);
	if (rc->dist < 0.4)
		rc->dist = 0.4;

	rc->tx = (double)rc->texture->size.x * rc->where;
	for (int blurp = 0; blurp < rc->hauteur * 2; ++blurp)
	{
		rc->ty = (double)rc->texture->size.y * (blurp / (rc->hauteur * 2));
		draw_pixel(e->wolf3d, i, e->wolf3d->vb_height / 2 - rc->hauteur + blurp,
			rc->texture->data[rc->tx + rc->ty * rc->texture->size.x]);
	}
	draw_pixel(e->wolf3d, i, rc->floor++, 0);
	draw_pixel(e->wolf3d, i, rc->sky--, 0);
	while (rc->floor <= (int)e->wolf3d->vb_height)
	{
		draw_pixel(e->wolf3d, i, rc->floor++, 0xffffff);
		draw_pixel(e->wolf3d, i, rc->sky--, 0x505050);
	}
}

void	ray_caster(t_player p, t_env *e, int mc)
{
	t_raycast	rc;
	size_t		i;
	rc.sizewall = 650;

	rc.texture = assets_get_texture(&e->assets, "Wall_1", NULL);

	i = -1;

	if (mc)
		rc.fov = 60.0;
	else
		rc.fov = 60.0;
	if (mc)
		while (++i < e->wolf3d->vb_width)
			draw_wolf(e, p, &rc, i);
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
