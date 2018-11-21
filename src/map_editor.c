#include "../inc/env.h"
#include "../inc/glfw_wrapper.h"

t_header	*map_scale(t_header *map, uint32_t width, uint32_t height)
{
	t_header	*out;
	uint32_t	x;
	uint32_t	y;
	
	if (width == map->width && height == map->height)
		return (map);
	if ((out = malloc(sizeof(t_header) + width * height)) == NULL)
	{
		free(map);
		return (NULL);
	}
	*out = (t_header){.magic = W3D_MAGIC, .height = height, .width = width,
		.startx = width / 2, .starty = height / 2, .look = 0};
	y = -1;
	while (++y < height && y < map->height)
	{
		x = -1;
		while (++x < width && map->width)
			out->map[x + y * width] = map->map[x + y * map->width];
	}
	free(map);
	return (out);
}

t_header	*map_editor(void)
{
	t_header		*out;
	t_glfw_window	*win;

	if ((out = default_map()) == NULL)
		return (NULL);
	if ((win = glfw_new_window(out->width * 25, out->height * 25,
					"map editor", NULL)) == NULL)
	{
		free(out);
		return (NULL);
	}
	//
	while (!glfwWindowShouldClose(win->w))
	{
		//
		glfwPollEvents();
	}
	// glfw_remove_window(win);
	return (out);
}
