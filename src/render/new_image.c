/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:38:50 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/17 20:47:20 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

t_mglfw_img	new_image(size_t width, size_t height)
{
	t_mglfw_img	out;

	glGenTextures(1, &out.id);
	glBindTexture(GL_TEXTURE_2D, out.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if ((out.buff = malloc(sizeof(uint32_t) * width * height)) == NULL)
		return ((t_mglfw_img){.id = 0, .width = 0, .height = 0, .buff = NULL});
	out.width = width;
	out.height = height;
	height = -1;
	while (++height < out.height && (width = -1))
		while (++width < out.width)
			out.buff[width + height * out.width] = 0x000000FF;
	glTextImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB_INTEGER,
		GL_UNSIGNED_INT_8_8_8_8, buff);
	return (out);
}
