/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:47:49 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:47:50 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int sign;

	sign = 1;
	i = 0;
	while (*str == ' ' || ((*str >= '\t') && (*str <= '\r')))
		str++;
	if ((*str == '-') || (*str == '+'))
		sign = (*str++ == '-') ? -1 : 1;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		i = (i * 10) + (*str++) - '0';
	return (sign * i);
}
