/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:39:35 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:32:15 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dda_init(t_gen *gen)
{
	gen->dda = malloc(sizeof(t_dda));
	if (!gen->dda)
		return (0);
	gen->dda->delta_x = 0;
	gen->dda->delta_y = 0;
	gen->dda->side = 0;
	gen->dda->side_x = 0;
	gen->dda->side_y = 0;
	gen->dda->wall_hit = 0;
	gen->dda->step_x = 0;
	gen->dda->step_y = 0;
	gen->dda->start_x = 0;
	gen->dda->start_y = 0;
	return (1);
}

int	render_scene_init(t_gen *gen)
{
	gen->render = malloc(sizeof(t_render_scene));
	if (!gen->render)
		return (0);
	gen->render->camera_x = 0;
	gen->render->draw_end = 0;
	gen->render->draw_start = 0;
	gen->render->line_height = 0;
	gen->render->ray_dir_x = 0;
	gen->render->ray_dir_y = 0;
	gen->render->texture_x = 0;
	gen->render->wall_x = 0;
	return (1);
}

int	player_move_init(t_gen *gen)
{
	gen->player_move = malloc(sizeof(t_player_move));
	if (!gen->player_move)
		return (0);
	gen->player_move->move_x = 0;
	gen->player_move->move_y = 0;
	return (1);
}

int	init_draw_enemy(t_gen *gen)
{
	gen->draw_enemy = malloc(sizeof(t_draw_enemy));
	if (!gen->draw_enemy)
		return (0);
	gen->draw_enemy->sprite_x = 0;
	gen->draw_enemy->sprite_y = 0;
	gen->draw_enemy->inv_det = 0;
	gen->draw_enemy->transform_x = 0;
	gen->draw_enemy->transform_y = 0;
	gen->draw_enemy->sprite_screen_x = 0;
	gen->draw_enemy->sprite_height = 0;
	gen->draw_enemy->draw_start_y = 0;
	gen->draw_enemy->draw_end_y = 0;
	gen->draw_enemy->color = 0;
	gen->draw_enemy->tex_y = 0;
	gen->draw_enemy->d = 0;
	gen->draw_enemy->sprite_width = 0;
	gen->draw_enemy->draw_start_x = 0;
	gen->draw_enemy->draw_end_x = 0;
	gen->draw_enemy->tex_x = 0;
	gen->draw_enemy->distance = 0;
	return (1);
}

int	exit_init(t_gen *gen)
{
	gen->exit = malloc(sizeof(t_exit));
	if (!gen->exit)
		return (0);
	gen->exit->active = false;
	return (1);
}
