/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_load_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_sjson_error	load_textures_names(t_sjson_object *obj, t_assets *out)
{
	char			resolved_path[PATH_MAX];
	t_sjson_string	*path;
	char			*name;
	size_t			it;

	it = 0;
	while (ft_swiss_table_iterate(obj, &it, (void**)&name, (void**)&path) == 1)
	{
		if (sjson_explorer((t_sjson_value*)path, "$s*", &path) != 1)
			return (SJSON_ERROR_KO);
		realpath(path->data, resolved_path);
		if (ft_swiss_table_find(&out->textures_names, name, NULL) == NULL)
		{
			if ((path = (t_sjson_string*)strdup(resolved_path)) == NULL)
				return (SJSON_ERROR_KO);
			if ((name = ft_strdup(name)) == NULL)
				return (SJSON_ERROR_KO);
			ft_swiss_table_insert(&out->textures_names, name, path);
		}
	}
	return (SJSON_ERROR_OK);
}

int				load_textures(t_assets *out)
{
	char	*path;
	t_bmp	*bmp;
	size_t	it;

	it = 0;
	printf("Loadding textures\n");
	while (ft_swiss_table_iterate(&out->textures_names, &it, NULL,
		(void**)&path) == 1)
		if (ft_swiss_table_find(&out->textures, path, NULL) == NULL)
		{
			if ((bmp = bmp_file_load(path)) == NULL)
				return (-1);
			ft_swiss_table_insert(&out->textures, path, bmp);
		}
	return (0);
}
