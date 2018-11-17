/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/11/17 18:20:05 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "glfw-3.2.1/glad/include/glad/glad.h"
// #include "glfw-3.2.1/include/GLFW/glfw3.h"

#include "../inc/env.h"

void	*print_key(GLFWwindow *win, int key, int scan, int act, int mod)
{
	(void)win;
	(void)mod;
	printf("%s: %s\n", glfwGetKeyName(key, scan), act == GLFW_PRESS ? "PRESS" : (act == GLFW_RELEASE ? "RELEASE" : "REPEAT"));
	return (NULL);
}

int	main(int ac, const char **av)
{
	static const char	*fragment =
		"#version 400 core\n"
		"in vec2 texture_coordinates;\n"
		"out vec4 FragColor;\n"
		"uniform sampler2D _texture;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(_texture, texture_coordinates);\n"
		"}\n\0";

	static const char	*vertex =
	"#version 400 core\n"
	"layout (location = 0) in vec3 _position;\n"
	"out vec2 texture_coordinates;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(_position, 1.0);\n"
	"	texture_coordinates = vec2(_position.x / 2.0 + 0.5, _position.y / 2.0 + 0.5);"
	"}\n\0";

	// unsigned char	test[SX * SY * 3];
	unsigned char	*test = malloc(SX * SY * 3);
	unsigned int	texture;
	unsigned int	vbo;
	unsigned int	vao;
	unsigned int	vs;
	unsigned int	fs;
	unsigned int	program;
	float			triangles[] = {-1.0, -1.0, 0.0,
								1.0, -1.0, 0.0,
								-1.0, 1.0, 0.0,
								1.0, 1.0, 0.0}; //GL_TRIANGLE_STRIP

	(void)av;
	if (ac == 2)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		GLFWwindow* window = glfwCreateWindow(SX, SY, "Hello World\n", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetKeyCallback(window, (GLFWkeyfun)&print_key);
		for (int x = 0; x < SX; ++x)
			for (int y = 0; y < SY; ++y)
			{
				test[(y * SX + x) * 3] = rand() % 256;
				test[(y * SX + x) * 3 + 1] = rand() % 256;
				test[(y * SX + x) * 3 + 2] = rand() % 256;
			}

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);

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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int tick = 0;
		int second = (int)time(NULL);
		while (!glfwWindowShouldClose(window))
		{
			for (int i = 0; i < SX * SY * 3; ++i)
				++test[i];
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SX, SY, 0, GL_RGB, GL_UNSIGNED_BYTE, test);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUseProgram(program);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glfwSwapBuffers(window);
			glfwPollEvents();
			if (second != (int)time(NULL))
			{
				second = (int)time(NULL);
				printf("fps: %d\n", tick);
				tick = 0;
			}
			++tick;
		}

		glDeleteShader(vs);
		glDeleteShader(fs);

		glfwTerminate();
	}
	else
		ft_putendl("Invalid Arguments");
	return (0);
}
