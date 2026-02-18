/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:46 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	release_movement_keys(int key, t_gen *gen)
{
	if (key == XK_w)
		gen->kboard->key_w = false;
	if (key == XK_s)
		gen->kboard->key_s = false;
	if (key == XK_a)
		gen->kboard->key_a = false;
	if (key == XK_d)
		gen->kboard->key_d = false;
	if (key == XK_Left)
		gen->kboard->key_left = false;
	if (key == XK_Right)
		gen->kboard->key_right = false;
	if (key == XK_Tab)
		gen->kboard->space = false;
}

void	release_modifier_keys(int key, t_gen *gen)
{
	if (key == XK_Control_L)
	{
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed;
			gen->enemy->move_speed = gen->player->move_speed;
		}
		else
		{
			gen->player->move_speed = 0.05;
			gen->player->rotate_speed = 0.045;
			gen->player->fov -= 0.07;
			gen->kboard->control_left = false;
		}
	}
	if (key == XK_Shift_L)
	{
		gen->player->move_speed = 0.05;
		gen->player->rotate_speed = 0.045;
		gen->kboard->shift_left = false;
	}
}

void	release_toggle_keys(int key, t_gen *gen)
{
	if (key == XK_m)
		gen->kboard->key_m = false;
	if (key == XK_x)
		gen->kboard->key_x = false;
	if (key == XK_z)
		gen->kboard->key_z = false;
	if (key == XK_f)
		gen->kboard->key_f = false;
	if (key == XK_l)
		gen->kboard->key_l = false;
	if (key == XK_t)
	{
		if (!gen->flags->terror_mode)
			stop_all_sounds(gen);
		gen->kboard->key_t = false;
	}
	if (key == XK_Caps_Lock)
		gen->kboard->key_caps_lock = false;
	if (key == XK_i)
		gen->kboard->key_i = false;
	if (key == XK_e)
		gen->kboard->key_e = false;
}

void	free_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->textures_info)
	{
		while (i < E_COUNT)
		{
			free(parse->textures_info[i]);
			parse->textures_info[i] = NULL;
			i++;
		}
		free(parse->textures_info);
		parse->textures_info = NULL;
	}
	if (parse->map)
		free_double(parse->map);
	if (parse)
		free(parse);
}
