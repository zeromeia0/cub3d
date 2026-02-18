/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:40:59 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_texture_array(t_texture **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = malloc(sizeof(t_texture));
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			return (0);
		}
		array[i]->data = NULL;
		array[i]->height = 0;
		array[i]->width = 0;
		array[i]->img = NULL;
		i++;
	}
	return (1);
}

static int	init_enemy_textures(t_gen *gen)
{
	if (!init_texture_array(gen->ghost_enemy, 4))
		return (0);
	if (!init_texture_array(gen->cthulhu_enemy, 2))
		return (0);
	if (!init_texture_array(gen->skeleton_enemy, 8))
		return (0);
	if (!init_texture_array(gen->winning_exit, 3))
		return (0);
	if (!init_texture_array(gen->hanged_skel, 4))
		return (0);
	return (1);
}

int	general_texture_init(t_gen *gen)
{
	if (!init_texture_array(gen->texture, 4))
		return (0);
	if (!init_texture_array(gen->terror_texture, 4))
		return (0);
	if (!init_enemy_textures(gen))
		return (0);
	return (1);
}

int	player_init(t_gen *gen)
{
	gen->player = malloc(sizeof(t_player));
	if (!gen->player)
		return (0);
	gen->player->x = 1;
	gen->player->y = 1;
	gen->player->dir_x = 0;
	gen->player->dir_y = 0;
	gen->player->plane_x = 0;
	gen->player->plane_y = 0;
	gen->player->move_speed = 0.05;
	gen->player->rotate_speed = DEFAULT_PLAYER_ROTATE_SPEED;
	gen->player->fov = DEFAULT_PLAYER_FOV;
	return (1);
}

int	arm_init(t_gen *gen)
{
	int	img_width;
	int	img_height;

	if (gen->arm)
		free_arm_object(gen, gen->arm);
	gen->arm = malloc(sizeof(t_img_data));
	if (!gen->arm)
		return (0);
	img_width = (int)gen->texture_data->arm_width;
	img_height = (int)gen->texture_data->arm_height;
	gen->arm->bits_pixel = 0;
	gen->arm->line_len = 0;
	gen->arm->endian = 0;
	gen->arm->width = 0;
	gen->arm->height = 0;
	return (1);
}
