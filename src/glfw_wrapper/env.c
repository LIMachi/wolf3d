/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/22 18:19:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/glfw_wrapper.h"

t_glfw_env	*set_env(t_glfw_env *set)
{
	static t_glfw_env	*singleton = NULL;

	if (set != NULL)
		singleton = set;
	return (singleton);
}

t_glfw_env	*env(void)
{
	return (set_env(NULL));
}
