/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:41:46 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_texture_x(t_gen *gen, t_rayhit hit, t_texture *tex,
		int *texture_x)
{
	*texture_x = (int)(gen->render->wall_x * (double)tex->width);
	if ((hit.side == 0 && gen->render->ray_dir_x < 0) || (hit.side == 1
			&& gen->render->ray_dir_y > 0))
		*texture_x = tex->width - *texture_x - 1;
}

void	draw_wall_slice(t_gen *gen, int x, t_texture *tex, double hit_dist)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	tex_x;

	tex_x = gen->render->texture_x;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	y = gen->render->draw_start - 1;
	while (++y < gen->render->draw_end)
	{
		d = y * 256 - WIN_HEIGHT * 128 + gen->render->line_height * 128;
		tex_y = ((d * tex->height) / gen->render->line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = tex->data[tex_y * tex->width + tex_x];
		if (gen->flags->terror_mode)
			color = apply_fog(color, hit_dist);
		copied_mlx_pixel_put(gen->img_data, x, y, color);
	}
}

void	draw_ceiling_slice(t_gen *gen, int x, int draw_start)
{
	int	y;
	int	color;

	y = 0;
	if (gen->flags->terror_mode)
		color = BLACK_CLR;
	else
		color = gen->texture_data->clng_color;
	while (y < draw_start)
	{
		copied_mlx_pixel_put(gen->img_data, x, y, color);
		y++;
	}
}

void	draw_floor_slice(t_gen *gen, int x, int draw_end)
{
	int	y;
	int	color;

	y = draw_end;
	if (gen->flags->terror_mode)
		color = BLACK_CLR;
	else
		color = gen->texture_data->flr_color;
	while (y < WIN_HEIGHT)
	{
		copied_mlx_pixel_put(gen->img_data, x, y, color);
		y++;
	}
}

void	get_wall_texture(t_gen *gen, t_rayhit hit, t_texture **tex)
{
	if (hit.type == HIT_WALL)
	{
		if (gen->flags->terror_mode)
			*tex = gen->terror_texture[hit.face];
		else
			*tex = gen->texture[hit.face];
	}
	else
	{
		if (gen->flags->terror_mode)
			*tex = gen->door_texture2;
		else
			*tex = gen->door_texture;
	}
}
