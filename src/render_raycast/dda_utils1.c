/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:44:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:30:58 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_step_x(t_gen *gen, double ray_x)
{
	if (ray_x < 0)
	{
		gen->dda->step_x = -1;
		gen->dda->side_x = (gen->player->x - gen->dda->start_x)
			* gen->dda->delta_x;
	}
	else
	{
		gen->dda->step_x = 1;
		gen->dda->side_x = (gen->dda->start_x + 1.0 - gen->player->x)
			* gen->dda->delta_x;
	}
}

void	init_step_y(t_gen *gen, double ray_y)
{
	if (ray_y < 0)
	{
		gen->dda->step_y = -1;
		gen->dda->side_y = (gen->player->y - gen->dda->start_y)
			* gen->dda->delta_y;
	}
	else
	{
		gen->dda->step_y = 1;
		gen->dda->side_y = (gen->dda->start_y + 1.0 - gen->player->y)
			* gen->dda->delta_y;
	}
}

void	dda_step(t_gen *gen)
{
	if (gen->dda->side_x < gen->dda->side_y)
	{
		gen->dda->side_x += gen->dda->delta_x;
		gen->dda->start_x += gen->dda->step_x;
		gen->dda->side = 0;
	}
	else
	{
		gen->dda->side_y += gen->dda->delta_y;
		gen->dda->start_y += gen->dda->step_y;
		gen->dda->side = 1;
	}
}

int	check_hit(t_gen *gen, bool interact, t_rayhit *hit)
{
	char	cell;

	if (gen->dda->start_y < 0 || gen->dda->start_y >= gen->parse->height)
		return (1);
	if (gen->dda->start_x < 0
		|| gen->dda->start_x
		>= (int)ft_strlen(gen->parse->map[gen->dda->start_y]))
		return (1);
	cell = gen->parse->map[gen->dda->start_y][gen->dda->start_x];
	if (cell == '1')
	{
		hit->type = HIT_WALL;
		return (1);
	}
	if (cell == 'D')
	{
		hit->type = HIT_DOOR;
		return (1);
	}
	if (cell == 'd' && interact)
	{
		hit->type = HIT_DOOR;
		return (1);
	}
	return (0);
}

void	finalize_hit(t_gen *gen, double ray_x, double ray_y, t_rayhit *hit)
{
	if (gen->dda->side == 0)
	{
		hit->dist = (gen->dda->start_x - gen->player->x + (1 - gen->dda->step_x)
				/ 2.0) / ray_x;
		if (ray_x > 0)
			hit->face = EAST;
		else
			hit->face = WEST;
	}
	else
	{
		hit->dist = (gen->dda->start_y - gen->player->y + (1 - gen->dda->step_y)
				/ 2.0) / ray_y;
		if (ray_y > 0)
			hit->face = NORTH;
		else
			hit->face = SOUTH;
	}
	hit->map_x = gen->dda->start_x;
	hit->map_y = gen->dda->start_y;
	hit->side = gen->dda->side;
}
