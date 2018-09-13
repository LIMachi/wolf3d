/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:48:57 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:48:58 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new_elem;
	t_list		*tmp;

	new_elem = NULL;
	while (lst)
	{
		if (new_elem == NULL)
		{
			new_elem = f(lst);
			tmp = new_elem;
		}
		else
		{
			tmp->next = f(lst);
			tmp = tmp->next;
		}
		lst = lst->next;
	}
	return (new_elem);
}
