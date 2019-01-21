/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
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

int		load(const char *path, t_env *env)
{
	int			fd;
	t_save_file	save;
	ssize_t		size;

	if (path == NULL || (fd = open(path, O_RDONLY)) == -1)
		return (-1);
	i_clear_map(env);
	if (read(fd, &save, sizeof(save)) != sizeof(save)
		|| save.magic != W3DS_MAGIC || save.config_file.magic != W3DC_MAGIC
		|| save.map_file.magic != W3DM_MAGIC || (size = save.map_file.height
			* save.map_file.width * sizeof(uint8_t)) == 0
		|| (env->map_file = malloc(sizeof(t_map_file) + size)) == NULL)
	{
		close(fd);
		return (-1);
	}
	env->config_file = save.config_file;
	*env->map_file = save.map_file;
	env->player.pos = (t_double2){.x = (double)save.posx / 100.0,
									.y = (double)save.posy / 100.0};
	env->player.look = (double)save.look / 100.0;
	if (read(fd, env->map_file->map, size) != size)
		i_clear_map(env);
	close(fd);
	return (0);
}
