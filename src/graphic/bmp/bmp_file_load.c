/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <fcntl.h>

static inline t_bitmap	*i_error(int fd,
								t_bitmap *out)
{
	if (out != NULL)
		free(out);
	if (fd != -1)
		close(fd);
	return (NULL);
}

static inline t_bitmap	*i_bmp_file_load(t_dib_header dib,
										int fd,
										t_bitmap_file_header head)
{
	int			offset;
	int			i;
	char		c;
	t_bitmap	*out;

	offset = head.offset - sizeof(t_bitmap_file_header) - dib.dib_size;
	if (dib.dib_size < 38)
	{
		dib.size_image = (dib.width * dib.bit_count) >> 3;
		dib.size_image += ((dib.width * dib.bit_count) & 7) != 0;
		dib.size_image *= dib.height;
	}
	if ((out = malloc(dib.size_image + sizeof(t_bitmap))) == NULL)
		return (i_error(fd, out));
	*out = (t_bitmap){.info = dib};
	i = -1;
	while (++i < offset)
		if (read(fd, &c, 1) != 1)
			return (i_error(fd, out));
	if (read(fd, out->data, dib.size_image) < dib.size_image)
		return (i_error(fd, out));
	close(fd);
	return (out);
}

t_bitmap				*bmp_file_load(const char *path)
{
	int						fd;
	t_bitmap_file_header	head;
	t_dib_header			dib;

	if (path == NULL || (fd = open(path, O_RDONLY | O_BINARY, 0)) == -1)
		return (NULL);
	if (read(fd, &head, sizeof(head)) < (int)sizeof(head)
			|| head.file_type != 0x4D42)
		return (i_error(fd, NULL));
	dib = (t_dib_header){.dib_size = 0};
	if (read(fd, &(dib.dib_size), sizeof(DWORD)) < (int)sizeof(DWORD)
			|| dib.dib_size - sizeof(DWORD) <= 0
			|| read(fd, &(dib.width), dib.dib_size - sizeof(DWORD))
				< (int)(dib.dib_size - sizeof(DWORD)))
		return (i_error(fd, NULL));
	return (i_bmp_file_load(dib, fd, head));
}
