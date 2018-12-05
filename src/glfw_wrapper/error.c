/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

void	*error(char *form, ...)
{
	va_list	va;
	void	*out;

	out = NULL;
	if (form == NULL)
		return (out);
	va_start(va, form);
	while (*form != '\0')
	{
		if (*form == 'd')
			close(va_arg(va, int));
		else if (*form == 'p')
			free(va_arg(va, void *));
		else if (*form == 'r')
			out = va_arg(va, void *);
		++form;
	}
	va_end(va);
	return (out);
}
