/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:53:18 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:53:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(unsigned char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *str)
{
	size_t	start;
	size_t	end;

	if (!str)
		return (NULL);
	start = 0;
	end = ft_strlen(str);
	if (!end)
		return (ft_strnew(0));
	while (is_space(str[start]))
		++start;
	while (is_space(str[end - 1]) && end > start)
		--end;
	if (!(end - start))
		return (ft_strnew(0));
	return (ft_strsub(str, start, end - start));
}
