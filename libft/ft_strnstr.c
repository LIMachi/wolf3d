/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:52:52 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:52:53 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t len2;

	len2 = ft_strlen(s2);
	if (!*s2)
		return ((char *)s1);
	while ((*s1) && (n-- >= len2))
	{
		if ((*s1 == *s2) && (ft_memcmp(s1, s2, len2) == 0))
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
