/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:53:15 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:53:16 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char *str, unsigned int start, size_t len)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strnew(len);
	if (!result)
		return (NULL);
	str += start;
	return (ft_strncpy(result, str, len));
}
