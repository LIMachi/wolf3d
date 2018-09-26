/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 20:08:47 by hmartzol          #+#    #+#             */
/*   Updated: 2018/09/17 20:26:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <render.h>

t_mglfw_win	new_window(size_t width, size_t height, const char *name)
{
	t_mglfw_win	out;

	if ((out.win = glfwCreateWindow(width, height, name, NULL, NULL)) == NULL)
		return ((t_mglfw_win){.win = NULL});
	out.width = width;
	out.height = height;
	out.name = name;
	glfwMakeContextCurrent(out.win);
	glClearColor(.0f, .0f, .0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(out.win);
	if ((out.vbuff = new_image(width, height)).buff == NULL)
	{
		glfwDestroyWindow(out.win);
		return ((t_mglfw_win){.win = NULL});
	}
	return (out);
}
