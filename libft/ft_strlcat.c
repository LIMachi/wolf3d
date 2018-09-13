/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:52:14 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:52:15 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t		s1;
	size_t		s2;
	size_t		i;

	s1 = ft_strlen(dest);
	s2 = ft_strlen(src);
	i = -1;
	if (n == 0)
		return (s1);
	if ((n - 1) <= (s1))
		return (s2 + n);
	while ((s1 + ++i) < (n - 1))
		dest[s1 + i] = src[i];
	dest[s1 + i] = '\0';
	return (s1 + s2);
}
