/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:53:34 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_move(t_player_move *move, double dir_x, double dir_y,
		double speed)
{
	move->move_x += dir_x * speed;
	move->move_y += dir_y * speed;
}

void	calculate_player_movement(t_gen *gen)
{
	t_player	*p;

	p = gen->player;
	gen->player_move->move_x = 0;
	gen->player_move->move_y = 0;
	if (gen->kboard->key_w)
		apply_move(gen->player_move, p->dir_x, p->dir_y, p->move_speed);
	if (gen->kboard->key_s)
		apply_move(gen->player_move, p->dir_x, p->dir_y, -p->move_speed);
	if (gen->kboard->key_a)
		apply_move(gen->player_move, p->plane_x, p->plane_y, -p->move_speed);
	if (gen->kboard->key_d)
		apply_move(gen->player_move, p->plane_x, p->plane_y, p->move_speed);
}
