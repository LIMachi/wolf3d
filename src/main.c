/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 11:52:12 by lmunoz-q          #+#    #+#             */
/*   Updated: 2018/09/13 23:08:05 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env.h"
#include "../libft/libft.h"
#include "../minilibx_macos/mlx.h"

#define SX 1200
#define SY 600

int main(int ac, const char **av)
{
	t_env	env;

	if (ac == 2)
	{
		if ((env.mlx = mlx_init()) == NULL)
			return (0);
		env.win = mlx_new_window(env.mlx, SX, SY, "coucou");
		env.img = mlx_new_image(env.mlx, SX, SY);
		env.timg = (int *)mlx_get_data_addr(env.img, &(env.bbp),
			&(env.size), &(env.endn));
	}
	else
		ft_putendl("Invalid Arguments");
	return 0;
}
