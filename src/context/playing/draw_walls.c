/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:53:16 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:53:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_walls(t_env *e, t_player p, t_raycast *rc, size_t i)
{
	t_double2	ray;
	int			j;
	int			d;
	int			l;

	ray = rotate_2d((t_double2){0, -1}, rc->angle + p.look);
	dda(e, p.pos, ray, rc);
	if (rc->dist < 0.4)
		rc->dist = 0.4;
	rc->tx = (double)rc->texture->size.x * rc->where;
	d = e->wolf3d->vb_height / 2 - rc->hauteur / 2;
	j = 0;
	if (d + j < 0)
		j = -d;
	l = rc->hauteur * 2;
	if (l + d >= (int)e->wolf3d->vb_height)
		l = e->wolf3d->vb_height - d;
	while (j++ < l)
	{
		rc->ty = (double)rc->texture->size.y * (j / rc->hauteur);
		draw_pixel(e->wolf3d, i, d + j,
			rc->texture->data[rc->tx + rc->ty * rc->texture->size.x]);
	}
	floor_casting(e, rc, &p, i);
}
