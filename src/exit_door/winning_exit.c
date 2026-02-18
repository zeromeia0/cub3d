/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winning_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:50:51 by vivaz-ca          #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_from_player(t_gen *gen, char **copy, int x, int y)
{
	if (x < 0 || y < 0 || x >= gen->parse->width || y >= gen->parse->height)
		return ;
	if (copy[y][x] == '1' || copy[y][x] == 'F')
		return ;
	copy[y][x] = 'F';
	flood_from_player(gen, copy, x + 1, y);
	flood_from_player(gen, copy, x - 1, y);
	flood_from_player(gen, copy, x, y + 1);
	flood_from_player(gen, copy, x, y - 1);
}

int	find_player_quadrant(t_gen *gen)
{
	if (gen->player->x < gen->parse->width / 2
		&& gen->player->y < gen->parse->height / 2)
		return (1);
	if (gen->player->x > gen->parse->width / 2
		&& gen->player->y < gen->parse->height / 2)
		return (2);
	if (gen->player->x < gen->parse->width / 2
		&& gen->player->y > gen->parse->height / 2)
		return (3);
	if (gen->player->x > gen->parse->width / 2
		&& gen->player->y > gen->parse->height / 2)
		return (4);
	return (0);
}

int	try_quadrant(t_gen *gen, char **copy, int quadrant)
{
	t_quad_bounds	quad;
	int				x;
	int				y;

	quad = get_quadrant_bounds(gen, quadrant);
	y = quad.start_y;
	while (y >= quad.end_y)
	{
		x = quad.start_x;
		while (x >= quad.end_x)
		{
			if (copy[y][x] == 'F')
			{
				gen->enemy[gen->enemy_count].size = 40;
				gen->enemy[gen->enemy_count].x = x + 0.5;
				gen->enemy[gen->enemy_count].y = y + 0.5;
				gen->enemy[gen->enemy_count].type = WINNING_STAR;
				gen->exit->active = true;
				return (1);
			}
			x--;
		}
		y--;
	}
	return (0);
}

void	set_valid_exit(t_gen *gen)
{
	char	**copy;
	int		player_q;
	int		order[4];
	int		i;

	i = 0;
	copy = create_copy_map(gen->parse);
	flood_from_player(gen, copy, (int)gen->player->x, (int)gen->player->y);
	player_q = find_player_quadrant(gen);
	get_quadrant_priority(player_q, order);
	gen->exit->active = false;
	while (i < 4)
	{
		if (try_quadrant(gen, copy, order[i]))
		{
			free_double(copy);
			return ;
		}
		i++;
	}
	free_double(copy);
}
