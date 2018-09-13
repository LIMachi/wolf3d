/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:49:49 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:49:50 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memcpy_reverse(void *dest, const void *src, size_t n)
{
	unsigned char		*s1;
	unsigned const char	*s2;

	s1 = dest;
	s2 = src;
	while (n--)
		s1[n] = s2[n];
	return (dest);
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src < dest && src + n > dest)
		return (ft_memcpy_reverse(dest, src, n));
	return (ft_memcpy(dest, src, n));
}
