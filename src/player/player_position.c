/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir_vector(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
}

void	set_plane_vector(t_player *p, char c)
{
	if (c == 'N')
	{
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'S')
	{
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (c == 'E')
	{
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	set_player_dir(t_player *p, char c)
{
	set_dir_vector(p, c);
	set_plane_vector(p, c);
}

void	search_in_matrix(t_gen *gen, char c)
{
	int	row;
	int	col;

	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == c)
			{
				gen->player->x = col + 0.5;
				gen->player->y = row + 0.5;
				set_player_dir(gen->player, c);
				return ;
			}
			col++;
		}
		row++;
	}
}

int	get_player_position(t_gen *gen)
{
	search_in_matrix(gen, 'N');
	search_in_matrix(gen, 'S');
	search_in_matrix(gen, 'E');
	search_in_matrix(gen, 'W');
	return (0);
}
