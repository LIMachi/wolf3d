/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static t_sjson_error	i_load_animations(t_sjson_object *obj, t_assets *out)
{
	(void)obj;
	(void)out;
	return (SJSON_ERROR_OK);
	/*
	size_t			i;
	t_sjson_string	*path;

	printf("Loadding animations\n");
	out->nb_animations = obj->nb_pairs;
	if (out->nb_animations == 0)
		return (SJSON_ERROR_KO);
	if (NULL == (out->anmination_names = malloc(sizeof(char*) * out->nb_animations)))
	{
		out->nb_animations = 0;
		return (SJSON_ERROR_KO);
	}
	if (NULL == (out->animations = malloc(sizeof(t_animations) * out->nb_animations)))
	{
		free(out->anmination_names);
		out->nb_animations = 0;
		return (SJSON_ERROR_KO);
	}
	i = -1;
	while (++i < obj->nb_pairs)
	{
		out->anmination_names[i] = ft_strdup(obj->pairs[i]->key->data);
		if (sjson_explorer(obj->pairs[i]->value, "$s*", &path) != 1)
			return (SJSON_ERROR_KO);
		assets_load_animation(path->data, &out->animations[i]);
	}
	return (SJSON_ERROR_OK);
	*/
}

static t_sjson_error	i_load_fonts(t_sjson_object *obj, t_assets *out)
{
	printf("Loadding fonts\n");
	(void)obj;
	(void)out;
	return (SJSON_ERROR_OK);
}

static t_sjson_error	i_load_music(t_sjson_object *obj, t_assets *out)
{
	printf("Loadding music\n");
	(void)obj;
	(void)out;
	return (SJSON_ERROR_OK);
}

/*
static t_sjson_error	i_load_textures(t_sjson_object *obj, t_assets *out)
{
	size_t			i;
	size_t			j;
	char			*key;
	t_sjson_value	*value;
	t_sjson_string	*path;

	printf("Loadding textures\n");
	out->nb_textures = obj->pair_count;
	if (out->nb_textures == 0)
		return (SJSON_ERROR_KO);
	if (NULL == (out->texture_names = malloc(sizeof(char*) * out->nb_textures)))
	{
		out->nb_textures = 0;
		return (SJSON_ERROR_KO);
	}
	if (NULL == (out->textures = malloc(sizeof(t_bmp*) * out->nb_textures)))
	{
		free(out->texture_names);
		out->nb_textures = 0;
		return (SJSON_ERROR_KO);
	}
	i = 0;
	j = 0;
	while (ft_swiss_table_iterate(obj, &i, (void**)&key, (void**)&value) == 1)
	{
		out->texture_names[j] = ft_strdup(key);
		if (sjson_explorer(value, "$s*", &path) != 1)
			return (SJSON_ERROR_KO);
		out->textures[j++] = bmp_file_load(path->data);
	}
	return (SJSON_ERROR_OK);
}
*/

static t_sjson_error	i_load_textures_names(t_sjson_object *obj, t_assets *out)
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

static inline int		i_load_textures(t_assets *out)
{
	char	*path;
	t_bmp	*bmp;
	size_t	it;

	it = 0;
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

t_assets				assets_load(const char *path)
{
	t_assets		out;
	t_sjson_value	*root;
	size_t			i;

	i = -1;
	while (++i < 8)
		if ((((t_swt_map*)&out)[i] = ft_swiss_table_create((t_swt_hashfun)
				ft_basic_hash, (t_swt_cmpfun)ft_strcmp)).groups == NULL)
			return (out);
	if (sjson_parse_file(path, &root, SJSON_FLAG_PRINT_ERRORS, 2)
			!= SJSON_ERROR_OK)
		return (out);
	sjson_explorer(root, "$o>#<>#<>#<>#", "animations", i_load_animations, &out,
		"fonts", i_load_fonts, &out, "music", i_load_music, &out, "textures",
		i_load_textures_names, &out);
	sjson_free(root);
	i_load_textures(&out);
	return (out);
}
