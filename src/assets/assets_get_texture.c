/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_get_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

t_bmp	*assets_get_texture(t_assets *assets, char *id, char *path)
{
	if (path == NULL)
	{
		if (id == NULL)
			return (ft_bmp_default());
		if (!(path = ft_swiss_table_find(&assets->textures_names, id, NULL)))
			return (ft_bmp_default());
	}
	return (ft_swiss_table_find(&assets->textures, path, ft_bmp_default()));
}
