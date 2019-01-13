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
		col.where = pos.y + col.dist * ray.y;
	if (col.face == 3)
		col.where = pos.x + col.dist * ray.x;
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
	int			floor;
	int			sky;
	double		hauteur;
	double		angle;
	double		real;
	t_bmp		*texture;

//	double sx;
//	double sy;

//	sx = (double)e->minimap->vb_width / (double)e->map_file->width;
//	sy = (double)e->minimap->vb_height / (double)e->map_file->height;

	texture = assets_get_texture(&e->assets, "Wall_1", NULL);

	if (mc)
		//fov = (double)e->config_file.fov / 100.0;
		fov = 60.0;
	else
		fov = 60.0;
	i = -1;
	while (++i < e->wolf3d->vb_width)
	{
		/*collision = ray_cast(e, p.pos,
			p.look - fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width);*/
		angle = -fov / 2.0 + fov * (double)i / (double)e->wolf3d->vb_width;
		ray = rotate_2d((t_double2){0, -1}, angle + p.look);
		df = ray_cast(e, p.pos, ray);
//		draw_line(e->minimap, vecftoveci(p.pos, sx, sy), vecftoveci(vecfadd(p.pos, vecfscale(ray, df.dist)), sx, sy), 0xFFFF00);
		if (df.dist < 0.4)
			df.dist = 0.4;
		real = df.dist * cos(DEG_TO_RAD * angle);
		hauteur = (sizewall) / real;
		floor = e->wolf3d->vb_height / 2 + hauteur;
		sky = e->wolf3d->vb_height / 2 - hauteur;
		if (mc)
		{
			int tx;
			int ty;
			tx = (double)texture->size.x * df.where;
//				printf("tx: %d\n", tx);
			for (int blurp = 0; blurp < hauteur * 2; ++blurp)
			{
				ty = (double)texture->size.y * (blurp / (hauteur * 2));
				draw_pixel(e->wolf3d, i, e->wolf3d->vb_height / 2 - hauteur + blurp,
					texture->data[tx + ty * texture->size.x]);
			}
			draw_pixel(e->wolf3d, i, floor++, 0);
			draw_pixel(e->wolf3d, i, sky--, 0);
			while (floor <= (int)e->wolf3d->vb_height)
			{
				draw_pixel(e->wolf3d, i, floor++, 0xffffff);
				draw_pixel(e->wolf3d, i, sky--, 0x505050);
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
