/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:21:27 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_player(t_gen *gen)
{
	int	center_tile;
	int	px;
	int	py;
	int	x;
	int	y;

	center_tile = gen->minimap->zoom_level / 2;
	px = center_tile * MINIMAP_PIXELS / gen->minimap->zoom_level;
	py = center_tile * MINIMAP_PIXELS / gen->minimap->zoom_level;
	y = 0;
	while (y < MINIMAP_PIXELS / gen->minimap->zoom_level)
	{
		x = 0;
		while (x < MINIMAP_PIXELS / gen->minimap->zoom_level)
		{
			copied_mlx_pixel_put(gen->img_data, px + x, py + y,
				MINIMAP_PLAYER_CLR);
			x++;
		}
		y++;
	}
}

void	process_fov_ray(t_gen *gen, int i, int num_rays)
{
	double	camera_x;
	double	ray_direction_x;
	double	ray_direction_y;

	camera_x = 2.0 * i / (num_rays - 1) - 1.0;
	ray_direction_x = gen->player->dir_x + gen->player->plane_x * camera_x;
	ray_direction_y = gen->player->dir_y + gen->player->plane_y * camera_x;
	direction_hits_wall(gen, ray_direction_x, ray_direction_y);
}

void	draw_minimap_fov(t_gen *gen)
{
	int	i;
	int	num_rays;

	num_rays = 20;
	i = 0;
	while (i < num_rays)
	{
		process_fov_ray(gen, i, num_rays);
		i++;
	}
}

void	draw_minimap_enemies(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->enemy_count)
	{
		draw_enemy_minimap(gen, i);
		i++;
	}
}

void	draw_minimap(t_gen *gen)
{
	int	start_x;
	int	start_y;

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	draw_minimap_area(gen, start_x, start_y);
	if (gen->flags->enemy_mini)
		draw_minimap_enemies(gen);
	draw_minimap_player(gen);
	draw_minimap_fov(gen);
}
