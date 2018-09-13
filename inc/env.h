/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/09/13 20:45:38 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdint.h>

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				sx;
	int				sy;
	int				*map;
	int				x;
	int				y;
}					t_env;

typedef struct		s_header
{
	uint32_t		magic;
	uint32_t		height;
	uint32_t		width;
	uint32_t		startx;
	uint32_t		starty;
	uint32_t		look;
	uint32_t		map[0];
}					t_header;

t_header	*head;
head = (t_header*)(
read(fd, &head.magic, sizeof(head.magic));
read(fd, &head.height, sizeof(head.height));
read(fd, &head.width, sizeof(head.width));



# endif
