/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_maps_in_dir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:18:52 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/09 17:44:00 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>
#include <dirent.h>

static inline char	*i_path(const char *dirpath, char *name)
{
	static char	path[PATH_MAX];
	char		tmp_path[PATH_MAX];
	size_t		l;

	ft_strcpy(tmp_path, dirpath);
	l = ft_strlen(dirpath);
	tmp_path[l++] = '/';
	ft_strcpy(&tmp_path[l], name);
	realpath(tmp_path, path);
	return (path);
}

int					get_saves_in_dir(const char *dirpath, char **buf,
	size_t buf_size)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				fd;
	int				size;
	uint32_t		magic;

	if (buf == NULL)
		buf_size = -1;
	if ((dirp = opendir(dirpath)) == NULL)
		return (-1);
	size = -1;
	while ((dp = readdir(dirp)) != NULL)
	{
		if ((fd = open(i_path(dirpath, dp->d_name), O_RDONLY)) == -1)
			continue ;
		magic = 0;
		read(fd, &magic, sizeof(uint32_t));
		if (magic == W3DS_MAGIC && ++size < (int)buf_size && buf != NULL)
			buf[size] = ft_strdup(i_path(dirpath, dp->d_name));
		close(fd);
	}
	closedir(dirp);
	return (size + 1);
}
