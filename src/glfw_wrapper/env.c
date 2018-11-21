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
