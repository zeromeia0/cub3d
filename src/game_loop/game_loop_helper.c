/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:54:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:10:53 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game_loop_part_one(t_gen *gen)
{
	int	i;

	update_player(gen);
	i = 0;
	gen->enemy->move_speed = gen->player->move_speed - 0.001;
	while (i < gen->enemy_count + 1)
	{
		gen->enemy[i].move_speed = gen->player->move_speed - 0.01;
		update_enemy_animation(gen->enemy, i);
		i++;
	}
	clear_image(gen->img_data, 0x000000);
	render_scene(gen);
	i = 0;
	while (i < gen->enemy_count + 1)
	{
		draw_enemy(gen, i);
		i++;
	}
	mouse_looking(gen);
}

void	game_loop_part_two(t_gen *gen)
{
	if (!gen->flags->terror_mode && gen->flags->minimap)
		draw_minimap(gen);
	if (!gen->flags->terror_mode)
		draw_arm(gen);
	else
		draw_terror_arm(gen);
	apply_vignette_to_image(gen, gen->img_data);
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	if (gen->flags->info && !gen->flags->terror_mode)
		print_info(gen);
}

void	clear_image(t_img_data *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			copied_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
