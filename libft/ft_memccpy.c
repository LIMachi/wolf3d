/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:49:06 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:49:07 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*s1;
	unsigned const char	*s2;

	s1 = dest;
	s2 = src;
	while (n--)
	{
		*s1 = *s2++;
		if (*s1 == (unsigned char)c)
			return ((void *)s1 + 1);
		s1++;
	}
	return (NULL);
}
