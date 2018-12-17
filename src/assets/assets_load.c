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

static void	i_load_animations(t_sjson_object *obj, t_assets *out)
{
	printf("Loadding animations\n");
	(void)obj;
	(void)out;
}

static void	i_load_fonts(t_sjson_object *obj, t_assets *out)
{
	printf("Loadding fonts\n");
	(void)obj;
	(void)out;
}

static void	i_load_music(t_sjson_object *obj, t_assets *out)
{
	printf("Loadding music\n");
	(void)obj;
	(void)out;
}

static void	i_load_textures(t_sjson_object *obj, t_assets *out)
{
	size_t			i;
	t_sjson_string	*path;

	printf("Loadding textures\n");
	out->nb_textures = obj->nb_pairs;
	if (out->nb_textures == 0)
		return ;
	if (NULL == (out->texture_names = malloc(sizeof(char*) * out->nb_textures)))
	{
		out->nb_textures = 0;
		return ;
	}
	if (NULL == (out->textures = malloc(sizeof(t_bmp*) * out->nb_textures)))
	{
		free(out->texture_names);
		out->nb_textures = 0;
		return ;
	}
	printf("Found %d textures\n", out->nb_textures);
	i = -1;
	while (++i < obj->nb_pairs)
	{
		out->texture_names[i] = ft_strdup(obj->pairs[i]->key->data);
		sjson_explorer(obj->pairs[i]->value, "$s*", &path);
		printf("got texture: %s\n", path->data);
		out->textures[i] = bmp_file_load(path->data);
	}
}

t_assets	assets_load(const char *path)
{
	t_assets		out;
	t_sjson_value	*root;

	out = (t_assets){.nb_animations = 0, .nb_fonts = 0, .nb_musics = 0,
		.nb_textures = 0};
	if (sjson_parse_file(path, &root, SJSON_FLAG_PRINT_ERRORS, 2)
			!= SJSON_ERROR_OK)
		return (out);
	//
	sjson_print(1, root, 0);
	//
	sjson_explorer(root, "$o>#<>#<>#<>#", "animations", i_load_animations, &out,
		"fonts", i_load_fonts, &out, "music", i_load_music, &out, "textures",
		i_load_textures, &out);
	if (out.nb_textures == 0)
	{
		out.nb_textures = 1;
		out.textures = malloc(sizeof(t_bmp *));
		out.textures[0] = ft_bmp_default();
		out.texture_names = malloc(sizeof(char*));
		out.texture_names[0] = ft_strdup("Wall");
	}
	sjson_free(root);
	return (out);
}
