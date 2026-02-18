/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:33:30 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:31:45 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_misc_toggles(int key, t_gen *gen)
{
	if (key == XK_space)
		gen->kboard->space = true;
	if (key == XK_Caps_Lock)
		toggle_flag(&gen->kboard->key_caps_lock, &gen->flags->mouse_on);
	if (key == XK_i)
		toggle_flag(&gen->kboard->key_i, &gen->flags->info);
	if (key == XK_m)
		toggle_flag(&gen->kboard->key_m, &gen->flags->minimap);
	if (key == XK_e)
		toggle_flag(&gen->kboard->key_e, &gen->flags->enemy_mini);
}

int	handle_exit(int keysys)
{
	if (keysys == XK_Escape)
		return (super_duper_hiper_free(), 1);
	return (0);
}

void	handle_terror_toggle(int key, t_gen *gen)
{
	if (key == XK_t && !gen->kboard->key_t)
	{
		gen->kboard->key_t = true;
		stop_all_sounds(gen);
		gen->player->move_speed = 0.1;
		gen->enemy->move_speed = gen->player->move_speed;
		gen->flags->terror_mode = !gen->flags->terror_mode;
		start_terror_music(gen);
		update_enemy_modes(gen);
		if (gen->flags->terror_mode)
		{
			if (gen->exit->active == false)
				set_valid_exit(gen);
		}
		else
			gen->exit->active = false;
	}
}

int	key_press(int key, t_gen *gen)
{
	if (key == XK_Escape)
		handle_exit(key);
	handle_movement_keys(key, gen);
	handle_modifier_keys(key, gen);
	handle_view_keys(key, gen);
	handle_toggle_keys(key, gen);
	handle_audio_keys(key, gen);
	return (0);
}

int	key_release(int key, t_gen *gen)
{
	release_movement_keys(key, gen);
	release_modifier_keys(key, gen);
	release_toggle_keys(key, gen);
	return (0);
}
