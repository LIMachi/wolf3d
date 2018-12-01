/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:05:35 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/14 15:35:42 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

/*
** <env.h>
** typedef struct s_header t_header
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

int	save_map(const char *path, t_header *header)
{
	int		fd;
	ssize_t	size;

	if (path == NULL || header == NULL
			|| (fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		return (-1);
	size = sizeof(t_header) + header->width * header->height * sizeof(uint8_t);
	if (write(fd, header, size) != size)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
