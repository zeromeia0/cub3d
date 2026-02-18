/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:05:41 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:06 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_images(t_gen *gen)
{
	if (!gen || !gen->img_data)
		return ;
	if (gen->img_data->vignette)
		free(gen->img_data->vignette);
	if (gen->img_data->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
	free(gen->img_data);
	gen->img_data = NULL;
}

static void	free_single_texture(t_gen *gen, t_texture *tex)
{
	if (!tex)
		return ;
	if (gen->mlx_data && gen->mlx_data->mlx_ptr && tex->img)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, tex->img);
	free(tex);
}

static void	free_texture_array(t_gen *gen, t_texture **tex, int count)
{
	int	i;

	if (!tex)
		return ;
	i = 0;
	while (i < count)
	{
		if (tex[i])
		{
			if (gen->mlx_data && gen->mlx_data->mlx_ptr && tex[i]->img)
				mlx_destroy_image(gen->mlx_data->mlx_ptr, tex[i]->img);
			free(tex[i]);
			tex[i] = NULL;
		}
		i++;
	}
}

void	free_all_resources(t_gen *gen)
{
	free_images(gen);
	free_texture_array(gen, gen->texture, 4);
	free_texture_array(gen, gen->terror_texture, 4);
	free_texture_array(gen, gen->ghost_enemy, 4);
	free_texture_array(gen, gen->cthulhu_enemy, 2);
	free_texture_array(gen, gen->skeleton_enemy, 8);
	free_texture_array(gen, gen->hanged_skel, 4);
	free_texture_array(gen, gen->winning_exit, 3);
	free_single_texture(gen, gen->door_texture);
	free_single_texture(gen, gen->door_texture2);
	if (gen->enemy)
		free(gen->enemy);
	if (gen->render)
		free(gen->render);
	if (gen->player_move)
		free(gen->player_move);
	if (gen->draw_enemy)
		free(gen->draw_enemy);
}

int	super_duper_hiper_free(void)
{
	t_gen	*gen;

	gen = gen_stuff();
	stop_all_sounds(gen);
	free_game_objects(gen);
	free_all_resources(gen);
	free_input_and_raycast(gen);
	free_config_and_parsing(gen);
	free_exit(gen);
	if (gen->mlx_data)
	{
		if (gen->mlx_data->win_ptr)
			mlx_destroy_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
		if (gen->mlx_data->mlx_ptr)
		{
			mlx_destroy_display(gen->mlx_data->mlx_ptr);
			free(gen->mlx_data->mlx_ptr);
		}
		free(gen->mlx_data);
	}
	exit(0);
}
