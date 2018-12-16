/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/11 11:49:12 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_double2	rotate_2d(t_double2 vec, double deg)
{
	return ((t_double2){.x = vec.x * cos(deg * DEG_TO_RAD)
						- vec.y * sin(deg * DEG_TO_RAD),
						.y = vec.x * sin(deg * DEG_TO_RAD)
						+ vec.y * cos(deg * DEG_TO_RAD)});
}
