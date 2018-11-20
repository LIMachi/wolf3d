/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:10:15 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/20 20:20:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/glfw_wrapper.h"

void	glfw_refresh_window(t_glfw_window *win)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, win->vb_width, win->vb_length, 0,
		GL_RGB, GL_UNSIGNED_BYTE, win->vb);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, win->texture);
	glUseProgram(win->program);
	glBindVertexArray(win->vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glfwSwapBuffers(win->w);
}
