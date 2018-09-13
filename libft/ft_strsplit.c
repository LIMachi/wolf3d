/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:53:04 by lmunoz-q          #+#    #+#             */
/*   Updated: 2017/11/26 18:53:05 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**add_str(char **list, char *str)
{
	size_t	elem;
	char	**new_list;

	if (!str || !*str)
		return (list);
	elem = 0;
	while (list[elem])
		++elem;
	new_list = malloc(sizeof(char *) * (elem + 2));
	if (new_list == NULL)
		return (NULL);
	elem = 0;
	while (list[elem])
	{
		new_list[elem] = list[elem];
		++elem;
	}
	new_list[elem++] = str;
	new_list[elem] = NULL;
	free(list);
	return (new_list);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**list;
	int		start;
	int		end;

	if (!str)
		return (NULL);
	list = malloc(sizeof(char *));
	if (list == NULL)
		return (NULL);
	list[0] = NULL;
	if (!*str)
		return (list);
	start = 0;
	end = 0;
	while (str[start])
	{
		while (str[start] == c)
			++start;
		end = start;
		while (str[end] != c && str[end] != '\0')
			++end;
		list = add_str(list, ft_strsub(str, start, end - start));
		start = end;
	}
	return (list);
}
