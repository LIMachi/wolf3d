/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2019/01/01 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

/*
** <env.h>
** typedef struct s_header t_map_file
*/

#include <fcntl.h>

/*
** <fcntl.h>
** int open(const char *path, int oflag, ...);
*/

#include <unistd.h>

/*
** <unistd.h>
** ssize_t write(int fildes, void *buf, size_t nbyte);
** int close(int fildes);
*/

int	save(const char *path, t_env *env)
{
	int			fd;
	ssize_t		size;
	t_save_file	save;

	if (path == NULL || env == NULL
			|| (fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	save.magic = W3DS_MAGIC;
	save.posx = (int32_t)(env->player.pos.x * 100.0);
	save.posy = (int32_t)(env->player.pos.y * 100.0);
	save.look = (int32_t)(env->player.look * 100.0);
	save.config_file = env->config_file;
	save.map_file = *env->map_file;
	size = save.map_file.width * save.map_file.height * sizeof(uint8_t);
	if (write(fd, &save, sizeof(t_save_file)) != sizeof(t_save_file)
			|| write(fd, env->map_file->map, size) != size)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
