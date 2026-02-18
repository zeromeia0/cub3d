/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:50:44 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ciclope_dos_xman(t_img_data *img, int *coords, int color)
{
	int	vars[5];

	init_line(coords, vars);
	draw_line(img, coords, vars, color);
}

void	init_map_and_delta(t_gen *gen, double ray_dir_x, double ray_dir_y,
		double *vars)
{
	double	player_x;
	double	player_y;
	double	map_x;
	double	map_y;

	player_x = gen->player->x;
	player_y = gen->player->y;
	map_x = (int)player_x;
	map_y = (int)player_y;
	vars[0] = map_x;
	vars[1] = map_y;
	vars[2] = fabs(5 / ray_dir_x);
	vars[3] = fabs(5 / ray_dir_y);
}

void	init_steps_and_sidedist(t_gen *gen, double ray_dir_x, double ray_dir_y,
		double *vars)
{
	double	player_x;
	double	player_y;

	player_x = gen->player->x;
	player_y = gen->player->y;
	if (ray_dir_x < 0)
		vars[4] = -1;
	else
		vars[4] = 1;
	if (ray_dir_x < 0)
		vars[5] = (player_x - vars[0]) * vars[2];
	else
		vars[5] = (vars[0] + 1.0 - player_x) * vars[2];
	if (ray_dir_y < 0)
		vars[6] = -1;
	else
		vars[6] = 1;
	if (ray_dir_y < 0)
		vars[7] = (player_y - vars[1]) * vars[3];
	else
		vars[7] = (vars[1] + 1.0 - player_y) * vars[3];
}

void	draw_ray_minimap(t_gen *gen, double *vars)
{
	double	start_x;
	double	start_y;
	double	px1;
	double	py1;
	int		coords[4];

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	px1 = (vars[0] - start_x + 0.5) * MINIMAP_PIXELS / gen->minimap->zoom_level;
	py1 = (vars[1] - start_y + 0.5) * MINIMAP_PIXELS / gen->minimap->zoom_level;
	px1 = ft_clamp(px1, 0, MINIMAP_PIXELS - 1);
	py1 = ft_clamp(py1, 0, MINIMAP_PIXELS - 1);
	coords[0] = MINIMAP_PIXELS / 2;
	coords[1] = MINIMAP_PIXELS / 2;
	coords[2] = (int)px1;
	coords[3] = (int)py1;
	ciclope_dos_xman(gen->img_data, coords, RED_CLR);
}

void	direction_hits_wall(t_gen *gen, double ray_dir_x, double ray_dir_y)
{
	double	vars[8];

	init_map_and_delta(gen, ray_dir_x, ray_dir_y, vars);
	init_steps_and_sidedist(gen, ray_dir_x, ray_dir_y, vars);
	perform_dda(gen, vars);
	draw_ray_minimap(gen, vars);
}
