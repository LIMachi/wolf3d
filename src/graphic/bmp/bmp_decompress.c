/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_decompress.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

inline static uint32_t	i_apply_mask(uint32_t val,
									uint32_t mask)
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

inline static void		i_bmp_decompress(t_bitmap *bmp,
										t_ubmp *out,
										t_vec p,
										int x)
{
	int	t1;
	int	t2;
	int	y;

	t1 = (bmp->info.height - p.y - 1) * bmp->info.width + p.x;
	out->data[t1] = 0;
	y = -1;
	while (++y < 4)
		out->data[t1] |= bmp->data[
			p.y * x + p.x * (bmp->info.bit_count >> 3) + y] << (y << 3);
	if (bmp->info.bit_count < 32)
		out->data[t1] &= (0xFFFFFFFF >> (32 - bmp->info.bit_count));
	if (bmp->info.bit_compression == 3)
	{
		t1 = out->data[t1];
		t2 = (bmp->info.alpha_bmask) ?
			i_apply_mask(t1, bmp->info.alpha_bmask) << 24 : 0xFF000000;
		t2 |= i_apply_mask(t1, bmp->info.red_bmask) << 16;
		t2 |= i_apply_mask(t1, bmp->info.green_bmask) << 8;
		t2 |= i_apply_mask(t1, bmp->info.blue_bmask);
		out->data[(bmp->info.height - p.y - 1) * bmp->info.width + p.x] = t2;
	}
	else
		out->data[t1] |= 0xFF000000;
}

t_ubmp					*bmp_decompress(t_bitmap *bmp)
{
	t_ubmp	*out;
	t_vec	p;
	int		x;

	if (bmp == NULL || (out = (t_ubmp*)malloc(sizeof(t_ubmp) + sizeof(uint32_t)
			* bmp->info.width * bmp->info.height)) == NULL)
		return (NULL);
	out->size = (t_vec){.x = bmp->info.width, .y = bmp->info.height};
	x = (bmp->info.width * bmp->info.bit_count) >> 3;
	x += ((bmp->info.width * bmp->info.bit_count) & 7) != 0;
	p.y = bmp->info.height;
	while (--p.y >= 0 && (p.x = -1))
		while (++p.x < x / (bmp->info.bit_count >> 3))
			i_bmp_decompress(bmp, out, p, x);
	return (out);
}
