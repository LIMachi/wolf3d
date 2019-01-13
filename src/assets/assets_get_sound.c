/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_get_sound.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/21 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

t_sound	*assets_get_sound(t_assets *assets, char *id, char *path)
{
	if (path == NULL)
	{
		if (id == NULL)
			return (NULL);
		if (!(path = ft_swiss_table_find(&assets->sounds_names, id, NULL)))
			return (NULL);
	}
	return (ft_swiss_table_find(&assets->sounds, path, NULL));
}
