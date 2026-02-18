/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winnin_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:11:56 by vivaz-ca          #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_quad_x_bounds(t_gen *gen, t_quad_bounds *b, int quadrant,
		int mid_x)
{
	if (quadrant == 1 || quadrant == 3)
	{
		b->start_x = mid_x - 1;
		b->end_x = 0;
	}
	else if (quadrant == 2 || quadrant == 4)
	{
		b->start_x = gen->parse->width - 1;
		b->end_x = mid_x;
	}
}

void	set_quad_y_bounds(t_gen *gen, t_quad_bounds *b, int quadrant,
		int mid_y)
{
	if (quadrant == 1 || quadrant == 2)
	{
		b->start_y = mid_y - 1;
		b->end_y = 0;
	}
	else if (quadrant == 3 || quadrant == 4)
	{
		b->start_y = gen->parse->height - 1;
		b->end_y = mid_y;
	}
}

t_quad_bounds	get_quadrant_bounds(t_gen *gen, int quadrant)
{
	t_quad_bounds	b;
	int				mid_x;
	int				mid_y;

	mid_x = gen->parse->width / 2;
	mid_y = gen->parse->height / 2;
	b.start_x = 0;
	b.end_x = 0;
	b.start_y = 0;
	b.end_y = 0;
	set_quad_x_bounds(gen, &b, quadrant, mid_x);
	set_quad_y_bounds(gen, &b, quadrant, mid_y);
	return (b);
}

void	get_quadrant_priority(int player_q, int order[4])
{
	if (player_q == 1)
		ft_memcpy(order, (int [4]){4, 3, 2, 1}, sizeof(int) * 4);
	else if (player_q == 2)
		ft_memcpy(order, (int [4]){3, 4, 1, 2}, sizeof(int) * 4);
	else if (player_q == 3)
		ft_memcpy(order, (int [4]){2, 1, 4, 3}, sizeof(int) * 4);
	else
		ft_memcpy(order, (int [4]){1, 2, 3, 4}, sizeof(int) * 4);
}
