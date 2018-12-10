/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 13:18:52 by hmartzol          #+#    #+#             */
/*   Updated: 2018/12/09 17:44:00 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_config_file	*default_config(t_env *env)
{
	env->config_file = (t_config_file){.magic = W3DC_MAGIC,
		.action = GLFW_MOUSE_BUTTON_1 | MASK_FLAG_MOUSE_BUTTON,
		.backward = GLFW_KEY_S, .forward = GLFW_KEY_W,
		.strafe_left = GLFW_KEY_A, .strafe_right = GLFW_KEY_D,
		.turn_left = GLFW_KEY_LEFT, .turn_right = GLFW_KEY_RIGHT,
		.fov = 6000};
	return (&env->config_file);
}
