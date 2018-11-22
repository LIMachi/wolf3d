/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_window.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:22:53 by hmartzol          #+#    #+#             */
/*   Updated: 2018/11/22 18:29:19 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/glfw_wrapper.h"

static inline int			i_program(const char *fragment, const char *vertex)
{
	GLuint	program;
	GLuint	vs;
	GLuint	fs;

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex, NULL);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment, NULL);
	glCompileShader(vs);
	glCompileShader(fs);
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return (program);
}

static inline t_glfw_window	*i_new_window(t_glfw_window *out, void *user_ptr)
{
	GLuint					vbo;
	static const GLfloat	triangles[12] = {-1.0, -1.0, 0.0, 1.0, -1.0, 0.0,
											-1.0, 1.0, 0.0, 1.0, 1.0, 0.0};

	glGenVertexArrays(1, &out->vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(out->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
						3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glGenTextures(1, &out->texture);
	glBindTexture(GL_TEXTURE_2D, out->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (env()->window != NULL)
		env()->window->prev = out;
	glfwSetWindowUserPointer(out->w, user_ptr);
	return (env()->window = out);
}

t_glfw_window				*glfw_new_window(size_t width,
											size_t height,
											char *name,
											void *user_ptr)
{
	t_glfw_window	*out;

	if ((out = malloc(sizeof(t_glfw_window))) == NULL)
		return (NULL);
	*out = (t_glfw_window){.prev = NULL, .next = env()->window,
		.w_width = width, .vb_height = height,
		.vb = malloc(width * height * 3), .vb_width = width,
		.w_height = height, .w = glfwCreateWindow(
			width, height, name, NULL, NULL)};
	if (out->vb == NULL || out->w == NULL)
	{
		free(out->vb);
		free(out->w);
		free(out);
		return (NULL);
	}
	glfwMakeContextCurrent(out->w);
	gladLoadGL();
	out->program = i_program("#version 400 core\nin vec2 texture_coordinates;ou"
	"t vec4 FragColor;uniform sampler2D _texture;void main(){FragColor = textur"
	"e(_texture, texture_coordinates);}", "#version 400 core\nlayout (location "
	"= 0) in vec3 _position;out vec2 texture_coordinates;void main(){gl_Positio"
	"n = vec4(_position, 1.0);texture_coordinates = vec2(_position.x / 2.0 + 0."
	"5, _position.y / 2.0 + 0.5);}");
	return (i_new_window(out, user_ptr));
}
