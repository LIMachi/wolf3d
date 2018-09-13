/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:48:42 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:48:43 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **begin_list, t_list *new_elem)
{
	if (*begin_list == NULL)
	{
		(*begin_list) = new_elem;
		return ;
	}
	while ((*begin_list)->next)
		*begin_list = (*begin_list)->next;
	(*begin_list)->next = new_elem;
}
