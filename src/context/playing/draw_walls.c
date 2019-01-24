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

static inline void	choose_face(t_raycast *rc, t_bmp **text)
{
	if (rc->face == 1)
		*text = rc->text1;
	else if (rc->face == 2)
		*text = rc->text2;
	else if (rc->face == 3)
		*text = rc->text3;
	else
		*text = rc->text4;
}

void				draw_walls(t_env *e, t_player p, t_raycast *rc, size_t i)
{
	t_double2	ray;
	int			j;
	int			d;
	int			l;
	t_bmp		*text;

	ray = rotate_2d((t_double2){0, -1}, rc->angle + p.look);
	dda(e, p.pos, ray, rc);
	choose_face(rc, &text);
	rc->tx = (int)((double)text->size.x * rc->where) % text->size.x;
	d = e->wolf3d->vb_height / 2 - rc->hauteur / 2;
	j = 0;
	if (d + j < 0)
		j = -d;
	l = rc->hauteur * 2;
	if (l + d >= (int)e->wolf3d->vb_height)
		l = e->wolf3d->vb_height - d;
	while (j++ < l)
	{
		rc->ty = (int)((double)text->size.y * (j / rc->hauteur))
			% text->size.y;
		draw_pixel(e->wolf3d, i, d + j,
			text->data[rc->tx + rc->ty * text->size.x]);
	}
	floor_casting(e, rc, &p, i);
}
