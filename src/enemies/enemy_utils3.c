/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:36:14 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:32:33 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	enemy_visible(t_gen *gen, double *distance_out, int i)
{
	double	delta[2];
	double	distance;

	delta[0] = gen->enemy[i].x - gen->player->x;
	delta[1] = gen->enemy[i].y - gen->player->y;
	distance = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	if (distance_out)
		*distance_out = distance;
	if (distance > FOG_END)
		return (false);
	return (raycast_clear(gen, delta[0], delta[1], distance));
}

void	update_enemy_modes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->enemy_count)
	{
		if (gen->flags->terror_mode)
		{
			if (gen->enemy[i].type == ENEMY_SKELETON
				|| gen->enemy[i].type == ENEMY_SKELETON2)
				gen->enemy[i].type = HANGED_SKELETON;
		}
		else
			gen->enemy[i].type = gen->enemy[i].first_type;
		i++;
	}
}
