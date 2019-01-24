/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:41:09 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:41:11 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	skybox(t_env *e, t_player *p, t_raycast *rc, size_t i)
{
	int	tx;
	int	ty;
	int	y;

	y = (e->wolf3d->vb_height / 2) + 1;
	tx = ((rc->angle + p->look) / 90.0) * (double)rc->skybox->size.x;
	while (y--)
	{
		ty = ((double)y / (double)(e->wolf3d->vb_height / 2))
			* rc->skybox->size.y;
		draw_pixel(e->wolf3d, i, y, rc->skybox->data[tx + ty
			* rc->skybox->size.x]);
	}
}
