/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:56:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_enemy(t_gen *gen, int i)
{
	t_enemy		*enemy;
	t_texture	*tex;
	int			stripe;

	if (enemy_dealer(gen, &tex, &enemy, i) == 0)
		return ;
	draw_enemy_variable_initialization(gen, enemy);
	if (gen->draw_enemy->transform_y <= 0)
		return ;
	crazy_math_operations(gen);
	if (gen->flags->terror_mode && !enemy_visible(gen,
			&gen->draw_enemy->distance, i))
		return ;
	stripe = gen->draw_enemy->draw_start_x;
	while (stripe < gen->draw_enemy->draw_end_x)
	{
		if (stripe > 0 && stripe < WIN_WIDTH && gen->draw_enemy->transform_y > 0
			&& gen->draw_enemy->transform_y < gen->rayhit->zbuffer[stripe])
			render_enemy_stripe(gen, tex, stripe);
		stripe++;
	}
}

void	draw_enemy_minimap(t_gen *gen, int i)
{
	int	start_x;
	int	start_y;
	int	px;
	int	py;

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	px = (gen->enemy[i].x - start_x) * MINIMAP_PIXELS
		/ gen->minimap->zoom_level;
	py = (gen->enemy[i].y - start_y) * MINIMAP_PIXELS
		/ gen->minimap->zoom_level;
	if (px < 0 || py < 0 || px >= MINIMAP_PIXELS || py >= MINIMAP_PIXELS)
		return ;
	draw_enemy_square(gen, px, py);
}

int	count_enemies_in_map(t_gen *gen)
{
	int	count;
	int	row;
	int	col;

	count = 0;
	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == 'X'
				|| gen->parse->map[row][col] == 'x'
				|| gen->parse->map[row][col] == 'Z')
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

void	set_enemy(t_gen *gen, t_enemy *enemy, int row, int col)
{
	char	c;

	c = gen->parse->map[row][col];
	gen->parse->map[row][col] = '0';
	enemy->x = col + 0.5;
	enemy->y = row + 0.5;
	if (c == 'X')
		enemy->type = ENEMY_GHOST;
	else if (c == 'x')
		enemy->type = ENEMY_CTHULHU;
	else if (c == 'Z')
	{
		if ((row + col) % 2 == 0)
			enemy->type = ENEMY_SKELETON;
		else
			enemy->type = ENEMY_SKELETON2;
	}
	else
		return ;
	enemy->first_type = enemy->type;
}

void	find_enemy_from_map(t_gen *gen, int i)
{
	int	row;
	int	col;

	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == 'X'
				|| gen->parse->map[row][col] == 'x'
				|| gen->parse->map[row][col] == 'Z')
			{
				set_enemy(gen, &gen->enemy[i], row, col);
				return ;
			}
			col++;
		}
		row++;
	}
}
