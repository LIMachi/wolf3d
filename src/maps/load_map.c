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
** ssize_t read(int fildes, void *buf, size_t nbyte);
** int close(int fildes);
*/

#include <stdlib.h>

/*
**  void *malloc(size_t size);
*/

static inline void	i_clear_map(t_env *env)
{
	if (env->map_file != NULL)
	{
		free(env->map_file);
		env->map_file = NULL;
	}
}

t_map_file			*load_map(const char *path, t_env *env)
{
	int			fd;
	t_map_file	tmp;
	ssize_t		size;

	if (path == NULL || (fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	i_clear_map(env);
	if (read(fd, &tmp, sizeof(tmp)) != sizeof(tmp) || tmp.magic != W3DM_MAGIC
		|| (size = tmp.height * tmp.width * sizeof(uint8_t)) == 0
		|| (env->map_file = malloc(sizeof(tmp) + size)) == NULL)
	{
		close(fd);
		return (NULL);
	}
	*env->map_file = tmp;
	env->player.pos = (t_double2){.x = env->map_file->startx + 0.5,
		.y = env->map_file->starty + 0.5};
	env->player.look = (double)env->map_file->look / 100.0;
	if (read(fd, env->map_file->map, size) != size)
		i_clear_map(env);
	close(fd);
	return (env->map_file);
}
