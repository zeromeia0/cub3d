/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:09:56 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_line(t_gen *gen, int *y, char *label, double value)
{
	char	*str;

	str = print_helper(label, value);
	*y += 11;
	mlx_string_put(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr, 10, *y,
		INFO_TEXT_COLOR, str);
	free(str);
}

static void	print_player_info(t_gen *gen, int *y)
{
	print_line(gen, y, "Direction x: ", gen->player->dir_x);
	print_line(gen, y, "Direction y: ", gen->player->dir_y);
	print_line(gen, y, "Plane x: ", gen->player->plane_x);
	print_line(gen, y, "Plane y: ", gen->player->plane_y);
	print_line(gen, y, "X: ", gen->player->x);
	print_line(gen, y, "Y: ", gen->player->y);
	print_line(gen, y, "FOV: ", gen->player->fov);
}

static void	print_mouse_minimap_info(t_gen *gen, int *y)
{
	print_line(gen, y, "Mouse x: ", (double)gen->mouse->x);
	print_line(gen, y, "Mouse y: ", (double)gen->mouse->y);
	print_line(gen, y, "Minimap zoom level: ", gen->minimap->zoom_level);
}

static void	print_speed_info(t_gen *gen, int *y)
{
	print_line(gen, y, "Player rotation speed: ", gen->player->rotate_speed);
	print_line(gen, y, "Player speed: ", gen->player->move_speed);
	print_line(gen, y, "Enemy speed: ", gen->enemy->move_speed);
	print_line(gen, y, "pbongiov's wallet this ammount of sigma coins: ", 20);
}

void	print_info(t_gen *gen)
{
	int	y;

	if (gen->flags->minimap)
		y = 220;
	else
		y = 10;
	print_player_info(gen, &y);
	print_mouse_minimap_info(gen, &y);
	print_speed_info(gen, &y);
}
