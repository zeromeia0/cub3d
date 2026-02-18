/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:06 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(t_gen *gen, int w, int h)
{
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height, WINDOW_NAME);
	if (!gen->mlx_data->win_ptr)
		return (1);
	gen->arm->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM,
			&w, &h);
	if (!gen->arm->img)
		return (printf("Error\nError: failed to load arm image\n"), 1);
	gen->arm->addr = mlx_get_data_addr(gen->arm->img, &gen->arm->bits_pixel,
			&gen->arm->line_len, &gen->arm->endian);
	return (0);
}

int	start_window(t_gen *gen, char *argv)
{
	(void)argv;
	if (window_init(gen, 0, 0) == 1)
		return (printf("Error\nError: cound't initiate window"), 1);
	get_player_position(gen);
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,
			&gen->img_data->bits_pixel, &gen->img_data->line_len,
			&gen->img_data->endian);
	gen->img_data->height = gen->mlx_data->win_height;
	gen->img_data->width = gen->mlx_data->win_width;
	init_vignette(gen->img_data);
	mlx_hook(gen->mlx_data->win_ptr, 2, KeyPressMask, key_press, gen);
	mlx_hook(gen->mlx_data->win_ptr, 3, KeyReleaseMask, key_release, gen);
	mlx_hook(gen->mlx_data->win_ptr, DestroyNotify, KeyPressMask,
		super_duper_hiper_free, NULL);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, game_loop, gen);
	mlx_loop(gen->mlx_data->mlx_ptr);
	return (0);
}
