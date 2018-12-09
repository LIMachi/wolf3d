/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:13:30 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/14 15:35:10 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

#include <fcntl.h>

/*
** <fcntl.h>
** int open(const char *path, int oflag, ...);
*/

#include <unistd.h>

/*
** <unistd.h>
** ssize_t read(int fildes, void *buf, size_t nbyte);
** int close(int fildes);
*/

t_config_file	*load_config(const char *path, t_env *env)
{
	int				fd;
	t_config_file	tmp;

	if (path == NULL || (fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, &tmp, sizeof(tmp)) != sizeof(tmp) || tmp.magic != W3DC_MAGIC)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	env->config_file = tmp;
	return (&env->config_file);
}
