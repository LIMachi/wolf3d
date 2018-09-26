/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel_to_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 20:01:12 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/17 20:06:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

int	put_pixel_to_img(t_mglfw_img *img, size_t x, size_t y, uint32_t color)
{
	if (img == NULL || img->buff == NULL || x >= img->width || y >= img->height)
		return (-1);
	img->buff[x + y * img->width] = color;
	return (0);
}
