/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:44:36 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:44:38 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void	draw_floor(t_env *e, t_raycast *rc, t_player *p, size_t i)
{
	while (rc->floor <= (int)e->wolf3d->vb_height)
	{
		rc->cdist = (e->wolf3d->vb_height / (2.0 * rc->floor -
			e->wolf3d->vb_height));
		rc->fact = ((rc->cdist) / (rc->real));
		rc->cfx = rc->fact * rc->floorx + (1.0 - rc->fact) * p->pos.x;
		rc->cfy = rc->fact * rc->floory + (1.0 - rc->fact) * p->pos.y;
		rc->tx = (int)(rc->cfx * rc->texturen2->size.x) % rc->texturen2->size.x;
		rc->ty = (int)(rc->cfy * rc->texturen2->size.y) % rc->texturen2->size.y;
		draw_pixel(e->wolf3d, i, rc->floor++, rc->texturen2->data[rc->tx
			+ rc->ty * rc->texturen2->size.x]);
	}
}

void		floor_casting(t_env *e, t_raycast *rc, t_player *p, size_t i)
{
	if (rc->face == 0)
	{
		rc->floorx = rc->mapx;
		rc->floory = rc->mapy + rc->where;
	}
	else if (rc->face == 2)
	{
		rc->floorx = rc->mapx + 1.0;
		rc->floory = rc->mapy + rc->where;
	}
	else if (rc->face == 1)
	{
		rc->floorx = rc->mapx + rc->where;
		rc->floory = rc->mapy;
	}
	else
	{
		rc->floorx = rc->mapx + rc->where;
		rc->floory = rc->mapy + 1.0;
	}
	draw_floor(e, rc, p, i);
}
