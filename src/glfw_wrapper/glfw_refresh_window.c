/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_refresh_window.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:10:15 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:36 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>

void	glfw_refresh_window(t_glfw_window *win)
{
	GLFWwindow	*w;

	w = glfwGetCurrentContext();
	glfwMakeContextCurrent(win->w);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, win->vb_width, win->vb_height, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, win->vb);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, win->texture);
	glUseProgram(win->program);
	glBindVertexArray(win->vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glfwSwapBuffers(win->w);
	glfwMakeContextCurrent(w);
}
