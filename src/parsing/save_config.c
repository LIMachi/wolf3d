/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:05:35 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/14 15:35:42 by lmunoz-q         ###   ########.fr       */
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
** ssize_t write(int fildes, void *buf, size_t nbyte);
** int close(int fildes);
*/

int	save_config(const char *path, t_config_file *config_file)
{
	int		fd;

	if (path == NULL || config_file == NULL
		|| (fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	if (write(fd, config_file, sizeof(*config_file)) != sizeof(*config_file))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
