/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:55:00 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:55:02 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static inline void	i_dda(t_env *env, t_raycast *rc, t_double2 *pos,
	t_double2 *ray)
{
	if (rc->face == 0)
		rc->dist = (rc->mapx - pos->x + (1.0 - rc->stepx) / 2.0) / ray->x;
	else
		rc->dist = (rc->mapy - pos->y + (1.0 - rc->stepy) / 2.0) / ray->y;
	if (rc->stepx < 0 && rc->face == 0)
		rc->face = 2;
	if (rc->stepy < 0 && rc->face == 1)
		rc->face = 3;
	if (rc->face == 0 || rc->face == 2)
		rc->where = pos->y + rc->dist * ray->y;
	else
		rc->where = pos->x + rc->dist * ray->x;
	rc->where -= (int)rc->where;
	rc->real = rc->dist * cos(DEG_TO_RAD * rc->angle);
	if (rc->real <= 0.000001)
		rc->real = 0.000001;
	rc->hauteur = (int)(env->wolf3d->vb_height / rc->real);
	rc->floor = env->wolf3d->vb_height / 2.0 + rc->hauteur / 2.0;
	rc->sky = env->wolf3d->vb_height / 2.0 - rc->hauteur / 2.0;
	if (rc->floor >= (int)env->wolf3d->vb_height)
		rc->floor = env->wolf3d->vb_height - 1;
	if (rc->sky < 0)
		rc->sky = 0;
}

void				dda(t_env *env, t_double2 pos, t_double2 ray, t_raycast *rc)
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
		if (rc->mapx < 0 || rc->mapx >= (int)env->map_file->width
			|| rc->mapy < 0 || rc->mapy >= (int)env->map_file->height)
			rc->hit = 1;
		else if (env->map_file->map[rc->mapx + rc->mapy * env->map_file->width]
			> 0)
			rc->hit = 1;
	}
	i_dda(env, rc, &pos, &ray);
}
