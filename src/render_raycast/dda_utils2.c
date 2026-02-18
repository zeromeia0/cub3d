/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:00:40 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	perform_dda(t_gen *gen, double *vars)
{
	double	hit;

	hit = 0;
	while (!hit)
	{
		if (vars[5] < vars[7])
		{
			vars[5] = vars[5] + vars[2];
			vars[0] = vars[0] + vars[4];
		}
		else
		{
			vars[7] = vars[7] + vars[3];
			vars[1] = vars[1] + vars[6];
		}
		if (is_wall(gen, vars[0], vars[1]))
			hit = 1;
	}
}

void	draw_line(t_img_data *img, int *coords, int *vars, int color)
{
	int	err2;

	while (1)
	{
		copied_mlx_pixel_put(img, coords[0], coords[1], color);
		if (coords[0] == coords[2] && coords[1] == coords[3])
			break ;
		err2 = 2 * vars[4];
		if (err2 > -vars[1])
		{
			vars[4] = vars[4] - vars[1];
			coords[0] = coords[0] + vars[2];
		}
		if (err2 < vars[0])
		{
			vars[4] = vars[4] + vars[0];
			coords[1] = coords[1] + vars[3];
		}
	}
}

void	open_close_door(t_gen *gen)
{
	double		ray_x;
	double		ray_y;
	t_rayhit	hit;
	char		*cell;

	ray_x = gen->player->dir_x;
	ray_y = gen->player->dir_y;
	hit = castrate(gen, ray_x, ray_y, 1);
	if (hit.type != HIT_DOOR)
		return ;
	if (hit.dist > 1.5)
		return ;
	cell = &gen->parse->map[hit.map_y][hit.map_x];
	if (*cell == 'D')
		*cell = 'd';
	else if (*cell == 'd')
		*cell = 'D';
}
