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

static inline uint32_t	i_mask(uint32_t val, uint32_t mask)
{
	uint32_t	i;

	if (mask == 0 || val == 0)
		return (0);
	i = val & mask;
	while (!(mask & 1))
	{
		i >>= 1;
		mask >>= 1;
	}
	if (mask >= 0xFF)
		return (i);
	return ((uint32_t)(((double)0xFF) * (double)i / (double)mask));
}

static inline uint32_t	i_bytes(t_vec pos, t_bmp_file f, int bpl)
{
	uint32_t c;
	uint32_t t;

	c = *(uint32_t*)&f.data[pos.x * (f.dib.bit_per_pixel >> 3) + pos.y * bpl];
	if (f.dib.palette != 0)
		c = f.color_palette[c % f.dib.palette];
	else if (f.dib.bit_per_pixel < 32)
		c &= 0xFFFFFFFF >> (32 - f.dib.bit_per_pixel);
	if (f.dib.compression == BI_BITFIELDS
			|| f.dib.compression == BI_ALPHABITFIELDS)
	{
		t = f.dib.compression == BI_ALPHABITFIELDS ?
			i_mask(c, f.dib.alpha_bmask) << 24 : 0xFF000000;
		t |= i_mask(c, f.dib.red_bmask) << 16;
		t |= i_mask(c, f.dib.green_bmask) << 8;
		c = t | i_mask(c, f.dib.blue_bmask);
	}
	else
		c |= 0xFF000000;
	return (c);
}

static inline t_bmp		*i_decompress(t_bmp_file f)
{
	t_bmp	*out;
	t_vec	p;
	int		bpl;

	if ((out = malloc(sizeof(t_bmp)
			+ sizeof(uint32_t) * f.dib.width * f.dib.height)) == NULL)
		return (error("pp", f.color_palette, f.data));
	out->size = (t_vec){.x = f.dib.width, .y = f.dib.height};
	p.y = -1;
	bpl = (f.dib.width * f.dib.bit_per_pixel) >> 3;
	bpl += ((f.dib.width * f.dib.bit_per_pixel) & 7) != 0;
	if (bpl & 3)
		bpl += 4 - (bpl & 3);
	while (++p.y < (int)f.dib.height && (p.x = -1))
		while (++p.x < (int)f.dib.width)
			out->data[p.x + (f.dib.height - p.y - 1) * f.dib.width]
				= i_bytes(p, f, bpl);
	if (f.color_palette)
		free(f.color_palette);
	free(f.data);
	return (out);
}

static inline t_bmp		*i_bmp_file_load(int fd, t_bmp_file f)
{
	int			i;

	if (f.dib.bit_per_pixel <= 8 && f.dib.palette == 0)
		f.dib.palette = (uint32_t)1 << f.dib.bit_per_pixel;
	if (f.dib.palette != 0)
	{
		f.color_palette = (uint32_t*)malloc(
			sizeof(uint32_t) * f.dib.palette);
		if (f.color_palette == NULL)
			return (error("d", fd));
		if (read(fd, f.color_palette, sizeof(uint32_t) * f.dib.palette)
				< (int)(sizeof(uint32_t) * f.dib.palette))
			return (error("dp", fd, f.color_palette));
	}
	i = sizeof(f.head) + f.dib.dib_size + sizeof(uint32_t) * f.dib.palette - 1;
	while (++i < (int)f.head.offset)
		if (read(fd, &(char[1]){0}, 1) != 1)
			return (error("dpp", fd, f.color_palette, f.data));
	if ((f.data = (uint8_t*)malloc(f.head.file_size - f.head.offset)) == NULL
			|| read(fd, f.data, f.head.file_size - f.head.offset)
				< f.head.file_size - f.head.offset)
		return (error("dpp", fd, f.color_palette, f.data));
	close(fd);
	return (i_decompress(f));
}

t_bmp					*bmp_file_load(const char *path)
{
	t_bmp_file				f;
	int						fd;

	if (path == NULL || (fd = open(path, O_RDONLY | O_BINARY, 0)) == -1)
		return (NULL);
	f.dib = (t_dib){.dib_size = 0, .compression = BI_RGB, .palette = 0};
	if (read(fd, &f.head, sizeof(f.head)) < (int)sizeof(f.head) ||
	(f.head.file_type != BITMAPSIGNATURE1
		&& f.head.file_type != BITMAPSIGNATURE2)
	|| read(fd, &f.dib, sizeof(DWORD)) < (int)sizeof(DWORD)
	|| f.dib.dib_size - sizeof(DWORD) <= 0
	|| strchr((char[8]){OS22XBITMAPHEADER, OS22XBITMAPHEADERV,
		BITMAPINFOHEADER, BITMAPV2INFOHEADER, BITMAPV3INFOHEADER,
		BITMAPV4HEADER, BITMAPV5HEADER, '\0'}, f.dib.dib_size) == NULL
	|| read(fd, &(f.dib.width), f.dib.dib_size - sizeof(DWORD))
		< (int)(f.dib.dib_size - sizeof(DWORD))
	|| (f.dib.compression != BI_RGB && f.dib.compression != BI_BITFIELDS
		&& f.dib.compression != BI_ALPHABITFIELDS))
	{
		close(fd);
		return (error("d", fd));
	}
	bzero(&(((char*)&f.dib)[f.dib.dib_size]), sizeof(f.dib) - f.dib.dib_size);
	return (i_bmp_file_load(fd, f));
}
