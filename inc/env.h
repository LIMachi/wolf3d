/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 18:37:25 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/09/15 21:57:17 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdint.h>

/*
** <stdint.h>
** typedef ... uint32_t
*/

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

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*timg;
	int				bbp;
	int				endn;
	int				size;
	int				x;
	int				y;
	float			look;
	t_header		*file;
}					t_env;

/*
** # define W3D_MAGIC *(uint32_t*)"w3d\n"
*/

t_header			*default_map(void);
t_header			*load_map(const char *path);
int					save_map(const char *path, t_header *header);

# define W3D_MAGIC	0x7733640A
#endif
