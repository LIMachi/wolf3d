/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_blend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:13:02 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:28:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

uint32_t			color_blend(uint32_t c1, uint32_t c2, double f)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	a = (uint32_t)(((double)((c1 >> 24) & 0xFF)) * f
		+ ((double)((c2 >> 24) & 0xFF)) * (1.0 - f));
	r = (uint32_t)(((double)((c1 >> 16) & 0xFF)) * f
		+ ((double)((c2 >> 16) & 0xFF)) * (1.0 - f));
	g = (uint32_t)(((double)((c1 >> 8) & 0xFF)) * f
		+ ((double)((c2 >> 8) & 0xFF)) * (1.0 - f));
	b = (uint32_t)(((double)(c1 & 0xFF)) * f
		+ ((double)(c2 & 0xFF)) * (1.0 - f));
	a = a > 255 ? 255 : a;
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	return ((a << 24) | (r << 16) | (g << 8) | b);
}
