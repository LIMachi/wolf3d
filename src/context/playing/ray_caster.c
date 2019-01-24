/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 04:49:31 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/01/24 04:49:33 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	ray_caster(t_player p, t_env *e, int mc, t_raycast rc)
{
	size_t		i;

	i = -1;
	if (mc)
		rc.fov = 60.0;
	else
		rc.fov = 60.0;
	if (mc)
		while (++i < e->wolf3d->vb_width)
		{
			rc.angle = -rc.fov / 2.0 + rc.fov * (double)i
				/ (double)e->wolf3d->vb_width;
			skybox(e, &p, &rc, i);
			draw_walls(e, p, &rc, i);
		}
}
