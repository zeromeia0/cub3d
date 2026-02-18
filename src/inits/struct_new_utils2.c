/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:40:07 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	terror_arm_init(t_gen *gen)
{
	int	img_width;
	int	img_height;

	if (gen->terror_arm)
		free_arm_object(gen, gen->terror_arm);
	gen->terror_arm = malloc(sizeof(t_img_data));
	if (!gen->terror_arm)
		return (0);
	img_width = (int)gen->texture_data->terror_arm_width;
	img_height = (int)gen->texture_data->terror_arm_height;
	gen->terror_arm->bits_pixel = 0;
	gen->terror_arm->line_len = 0;
	gen->terror_arm->endian = 0;
	gen->terror_arm->width = 0;
	gen->terror_arm->height = 0;
	gen->terror_arm->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
			USER_TERROR_HAND_XPM, &img_width, &img_height);
	gen->terror_arm->addr = mlx_get_data_addr(gen->terror_arm->img,
			&gen->terror_arm->bits_pixel, &gen->terror_arm->line_len,
			&gen->terror_arm->endian);
	return (1);
}

int	basic_mlx_init(t_gen *gen)
{
	gen->mlx_data->mlx_ptr = mlx_init();
	if (!gen->mlx_data->mlx_ptr)
		return (0);
	gen->mlx_data->win_ptr = NULL;
	gen->arm = NULL;
	gen->mlx_data->win_width = WIN_WIDTH;
	gen->mlx_data->win_height = WIN_HEIGHT;
	return (1);
}

int	init_flags(t_gen *gen)
{
	gen->flags = malloc(sizeof(t_flags));
	if (!gen->flags)
		return (0);
	gen->flags->info = true;
	gen->flags->terror_mode = false;
	gen->flags->minimap = true;
	gen->flags->mouse_on = true;
	gen->flags->enemy_mini = true;
	gen->flags->music_on = false;
	return (1);
}

int	def_values_init(t_gen *gen)
{
	gen->def_values = malloc(sizeof(t_def_values));
	if (!gen->def_values)
		return (0);
	gen->def_values->fov = gen->player->fov;
	gen->def_values->player_rotation_speed = gen->player->rotate_speed;
	gen->def_values->player_move_speed = gen->player->move_speed;
	gen->def_values->player_x = gen->player->x;
	gen->def_values->player_y = gen->player->y;
	gen->def_values->minimap_zoom_level = gen->minimap->zoom_level;
	gen->def_values->terror_player_move_speed
		= gen->def_values->player_move_speed
		+ 0.05;
	gen->def_values->env = NULL;
	gen->def_values->sounds.pids = malloc(sizeof(pid_t) * 128);
	gen->def_values->sounds.terror_music_pid = 0;
	gen->def_values->sounds.background_music_pid = 0;
	gen->def_values->sounds.terror_music_pid = 0;
	gen->def_values->sounds.count = 0;
	gen->def_values->sounds.capacity = 128;
	return (1);
}

int	enemy_init(t_gen *gen)
{
	int	i;

	i = -1;
	gen->enemy_count = count_enemies_in_map(gen);
	if (gen->enemy_count == 0)
		return (1);
	gen->enemy = calloc((gen->enemy_count + 1), sizeof(t_enemy));
	if (!gen->enemy)
		return (0);
	while (++i <= gen->enemy_count)
	{
		gen->enemy[i].move_speed = gen->def_values->player_move_speed;
		gen->enemy[i].size = 20;
		gen->enemy[i].x = 0;
		gen->enemy[i].y = 0;
		gen->enemy[i].enemy_frame = 0;
		gen->enemy[i].enemy_timer = 0;
		gen->enemy[i].type = ENEMY_SKELETON;
		gen->enemy[i].first_type = ENEMY_SKELETON;
		if (i == gen->enemy_count)
			gen->enemy[i].type = WINNING_STAR;
		else
			find_enemy_from_map(gen, i);
	}
	return (1);
}
