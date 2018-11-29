/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"

t_vector	rotate_2d(t_vector vec, double deg)
{
	return ((t_vector){.x = vec.x * cos(deg * DEG_TO_RAD)
						- vec.y * sin(deg * DEG_TO_RAD),
						.y = vec.x * sin(deg * DEG_TO_RAD)
						+ vec.y * cos(deg * DEG_TO_RAD)});
}
