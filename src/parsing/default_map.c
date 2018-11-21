/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:18:52 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/21 17:17:51 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include <stdlib.h>

/*
** <env.h>
** typedef struct s_header t_header
*/

t_header	*default_map(void)
{
	uint32_t				i;
	t_header				*out;
	static const t_header	head = {

	.magic = W3D_MAGIC,
	.height = 11,
	.width = 11,
	.startx = 5,
	.starty = 5,
	.look = 0};
	if ((out = malloc(sizeof(t_header) + 121 * sizeof(uint32_t))) == NULL)
		return (NULL);
	*out = head;
	i = -1;
	while (++i < 121)
		out->map[i] = i % 11 == 0 || i % 11 == 10 || i < 11 || i > 109;
	return (out);
}
