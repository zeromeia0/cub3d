/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:43:03 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	raycast_clear(t_gen *gen, double dx, double dy, double distance)
{
	double	x;
	double	y;
	double	step[2];
	double	traveled;

	step[0] = dx / distance * 0.1;
	step[1] = dy / distance * 0.1;
	x = gen->player->x;
	y = gen->player->y;
	traveled = 0;
	while (traveled < distance)
	{
		if (gen->parse->map[(int)y][(int)x] == '1'
			|| gen->parse->map[(int)y][(int)x] == 'D')
			return (false);
		x += step[0];
		y += step[1];
		traveled += 0.1;
	}
	return (true);
}

int	get_anim_stat_value(int type, int column)
{
	static int	stats[][3] = {{ENEMY_GHOST, 4, 10}, {ENEMY_CTHULHU, 2, 25},
	{ENEMY_SKELETON, 7, 8}, {ENEMY_SKELETON2, 3, 6}, {HANGED_SKELETON,
		4, 15}, {WINNING_STAR, 3, 3}, {-1, 0, 0}};
	int			i;

	i = 0;
	while (stats[i][0] != -1)
	{
		if (stats[i][0] == type)
			return (stats[i][column]);
		i++;
	}
	return (0);
}

void	get_enemy_anim_stats(int type, int *max_frames, int *speed)
{
	*max_frames = get_anim_stat_value(type, 1);
	*speed = get_anim_stat_value(type, 2);
}

void	update_enemy_animation(t_enemy *enemy, int i)
{
	int	max_frames;
	int	speed;

	get_enemy_anim_stats(enemy[i].type, &max_frames, &speed);
	if (speed <= 0)
		return ;
	enemy[i].enemy_timer++;
	if (enemy[i].enemy_timer >= speed)
	{
		enemy[i].enemy_timer = 0;
		enemy[i].enemy_frame = (enemy[i].enemy_frame + 1) % max_frames;
	}
}

int	enemy_dealer(t_gen *gen, t_texture **tex, t_enemy **enemy, int i)
{
	if (!gen->enemy || (gen->enemy[i].type == ENEMY_GHOST
			&& !gen->ghost_enemy[0]) || (gen->enemy[i].type == ENEMY_CTHULHU
			&& !gen->cthulhu_enemy[0] && gen->flags->terror_mode)
		|| ((gen->enemy[i].type == ENEMY_SKELETON
				|| gen->enemy[i].type == ENEMY_SKELETON2)
			&& !gen->skeleton_enemy[0]))
		return (0);
	*enemy = &gen->enemy[i];
	if ((*enemy)->type == ENEMY_GHOST && gen->flags->terror_mode)
		*tex = gen->ghost_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == ENEMY_CTHULHU && gen->flags->terror_mode)
		*tex = gen->cthulhu_enemy[(*enemy)->enemy_frame];
	else if (((*enemy)->type == ENEMY_SKELETON
			|| (*enemy)->type == ENEMY_SKELETON2) && !gen->flags->terror_mode)
		*tex = gen->skeleton_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == HANGED_SKELETON && gen->flags->terror_mode)
		*tex = gen->hanged_skel[(*enemy)->enemy_frame];
	else if ((*enemy)->type == WINNING_STAR && gen->flags->terror_mode
		&& gen->exit->active)
		*tex = gen->winning_exit[(*enemy)->enemy_frame];
	else
		return (0);
	return (1);
}
