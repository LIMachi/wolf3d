/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 20:01:34 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/17 20:21:39 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <stdint.h>
# include <stdlin.h>

typedef struct	s_mglfw_img
{
	unsigned int	id;
	size_t			width;
	size_t			height;
	uint32_t		*buff;
}				t_mglfw_img;

typedef struct	s_mglfw_win
{
	GLFWwindow		*win;
	size_t			width;
	size_t			height;
	const char		*name;
	t_mglfw_img		vbuff;
}				t_mglfw_win;

t_mglfw_img		new_image(size_t width, size_t height);
int				put_pixel_to_img(t_mglfw_img *img,
								size_t x, size_t y, uint32_t color);

#endif
