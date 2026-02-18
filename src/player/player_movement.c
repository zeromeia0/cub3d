/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:45:44 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:30:12 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_gen *gen, double angle)
{
	double	first_direction_x;
	double	first_plane_x;

	first_direction_x = gen->player->dir_x;
	first_plane_x = gen->player->plane_x;
	gen->player->dir_x = gen->player->dir_x * cos(angle) - gen->player->dir_y
		* sin(angle);
	gen->player->dir_y = first_direction_x * sin(angle) + gen->player->dir_y
		* cos(angle);
	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = first_plane_x * sin(angle) + gen->player->plane_y
		* cos(angle);
}

void	apply_player_movement(t_gen *gen, double nx, double ny)
{
	if (gen->kboard->space)
	{
		open_close_door(gen);
		gen->kboard->space = false;
	}
	if (gen->kboard->key_right)
		rotate_player(gen, gen->player->rotate_speed);
	if (gen->kboard->key_left)
		rotate_player(gen, -gen->player->rotate_speed);
	if (!collision(gen, gen->player->y, nx + gen->player_move->move_x))
		gen->player->x += gen->player_move->move_x;
	if (!collision(gen, ny + gen->player_move->move_y, gen->player->x))
		gen->player->y += gen->player_move->move_y;
	if (!gen->flags->terror_mode && !gen->kboard->control_left)
	{
		if (!gen->kboard->shift_left)
			gen->player->move_speed = 0.05;
	}
}

void	update_player(t_gen *gen)
{
	double	nx;
	double	ny;

	nx = gen->player->x;
	ny = gen->player->y;
	calculate_player_movement(gen);
	apply_player_movement(gen, nx, ny);
}

int	game_loop(t_gen *gen)
{
	double	dx;
	double	dy;
	double	distance;
	int		i;

	game_loop_part_one(gen);
	game_loop_part_two(gen);
	i = 0;
	while (i < gen->enemy_count + 1)
	{
		dx = gen->enemy[i].x - gen->player->x;
		dy = gen->enemy[i].y - gen->player->y;
		distance = sqrt(dx * dx + dy * dy);
		if (distance <= 0.65 && gen->flags->terror_mode
			&& i == gen->enemy_count)
			(printf("YOU WIN\n"), super_duper_hiper_free(), exit(1));
		else if (distance <= 0.65 && gen->flags->terror_mode
			&& (gen->enemy[i].type != ENEMY_SKELETON
				&& gen->enemy[i].type != ENEMY_SKELETON2
				&& gen->enemy[i].type != HANGED_SKELETON))
			(printf("YOU ARE DEAD\n"), super_duper_hiper_free(), exit(1));
		i++;
	}
	return (0);
}
