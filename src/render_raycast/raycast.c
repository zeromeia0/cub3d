/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:18:27 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rayhit	castrate(t_gen *gen, double ray_x, double ray_y, bool interact)
{
	t_rayhit	hit;

	if (!gen || !gen->parse || !gen->parse->map)
	{
		ft_putstr_fd("ERROR: gen->parse is NULL\n", 2);
		exit(1);
	}
	init_start(gen);
	init_delta(gen, ray_x, ray_y);
	init_step_x(gen, ray_x);
	init_step_y(gen, ray_y);
	while (!gen->dda->wall_hit)
	{
		dda_step(gen);
		if (check_hit(gen, interact, &hit))
			break ;
	}
	finalize_hit(gen, ray_x, ray_y, &hit);
	return (hit);
}

void	calculate_ray_params(t_gen *gen, int x)
{
	gen->render->camera_x = gen->player->fov * x / (double)WIN_WIDTH - 1.0;
	gen->render->ray_dir_x = gen->player->dir_x + gen->player->plane_x
		* gen->render->camera_x;
	gen->render->ray_dir_y = gen->player->dir_y + gen->player->plane_y
		* gen->render->camera_x;
}

void	calculate_wall_dimensions(double dist, int *line_h, int *draw_start,
		int *draw_end)
{
	*line_h = (int)(WIN_HEIGHT / dist);
	*draw_start = -*line_h / 2 + WIN_HEIGHT / 2;
	*draw_end = *line_h / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

void	calculate_wall_x(t_gen *gen, t_rayhit hit)
{
	if (hit.side == 0)
		gen->render->wall_x = gen->player->y + hit.dist
			* gen->render->ray_dir_y;
	else
		gen->render->wall_x = gen->player->x + hit.dist
			* gen->render->ray_dir_x;
	gen->render->wall_x -= floor(gen->render->wall_x);
}

void	render_scene(t_gen *gen)
{
	int			x;
	t_rayhit	hit;
	t_texture	*tex;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_ray_params(gen, x);
		hit = castrate(gen, gen->render->ray_dir_x, gen->render->ray_dir_y, 0);
		gen->rayhit->zbuffer[x] = hit.dist;
		calculate_wall_dimensions(hit.dist, &gen->render->line_height,
			&gen->render->draw_start, &gen->render->draw_end);
		calculate_wall_x(gen, hit);
		get_wall_texture(gen, hit, &tex);
		calculate_texture_x(gen, hit, tex, &gen->render->texture_x);
		draw_wall_slice(gen, x, tex, hit.dist);
		draw_ceiling_slice(gen, x, gen->render->draw_start);
		draw_floor_slice(gen, x, gen->render->draw_end);
		x++;
	}
}
