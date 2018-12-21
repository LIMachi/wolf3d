/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <lmunoz-q@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/12/16 23:26:13 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <glfw_wrapper.h>
#include <wolf3d.h>

int	context_end(t_env *env)
{
	glfwTerminate();
	sound_player_finish();
	//assets_unload(env);
	save_config(WOLF3D_CONFIG_W3C_PATH, &env->config_file);
	return (0);
}
