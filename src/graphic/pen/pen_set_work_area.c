/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pen_set_work_area.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

int	pen_set_work_area(t_glfw_window *win, t_vec top_left, t_vec bottom_right)
{
	if (win == NULL)
		return (-1);
	win->pen.top_left = top_left;
	win->pen.bottom_right = bottom_right;
	return (0);
}
