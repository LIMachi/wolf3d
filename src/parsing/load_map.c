/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:13:30 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/13 22:40:12 by hmartzol         ###   ########.fr       */
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
** ssize_t read(int fildes, void *buf, size_t nbyte);
** int close(int fildes);
*/

#include <stdlib.h>

/*
**  void *malloc(size_t size);
*/

t_header	*load_map(const char *path)
{
	int			fd;
	t_header	*file;
	t_header	tmp;
	ssize_t		size;

	if (path == NULL || (fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, &tmp, sizeof(tmp)) != sizeof(tmp) || tmp.magic != W3D_MAGIC)
		return (NULL);
	size = tmp.height * tmp.width * sizeof(uint32_t);
	if ((file = malloc(sizeof(tmp) + size)) == NULL)
		return ((t_header*)(close(fd) & 0ll));
	*file = tmp;
	if (read(fd, file->map, size) != size)
		return ((t_header*)(close(fd) & 0ll));
	close(fd);
	return (file);
}
