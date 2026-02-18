/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:46:09 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_enemy_variable_initialization(t_gen *gen, t_enemy *enemy)
{
	gen->draw_enemy->sprite_x = enemy->x - gen->player->x;
	gen->draw_enemy->sprite_y = enemy->y - gen->player->y;
	gen->draw_enemy->inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y
			- gen->player->dir_x * gen->player->plane_y);
	gen->draw_enemy->transform_x = gen->draw_enemy->inv_det
		* (gen->player->dir_y * gen->draw_enemy->sprite_x - gen->player->dir_x
			* gen->draw_enemy->sprite_y);
	gen->draw_enemy->transform_y = gen->draw_enemy->inv_det
		* (-gen->player->plane_y * gen->draw_enemy->sprite_x
			+ gen->player->plane_x * gen->draw_enemy->sprite_y);
}

void	crazy_math_operations(t_gen *gen)
{
	gen->draw_enemy->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1
				+ gen->draw_enemy->transform_x / gen->draw_enemy->transform_y));
	gen->draw_enemy->sprite_height = abs((int)(WIN_HEIGHT
				/ gen->draw_enemy->transform_y));
	gen->draw_enemy->draw_start_y = -gen->draw_enemy->sprite_height / 2
		+ WIN_HEIGHT / 2;
	gen->draw_enemy->draw_end_y = gen->draw_enemy->sprite_height / 2
		+ WIN_HEIGHT / 2;
	if (gen->draw_enemy->draw_start_y < 0)
		gen->draw_enemy->draw_start_y = 0;
	if (gen->draw_enemy->draw_end_y >= WIN_HEIGHT)
		gen->draw_enemy->draw_end_y = WIN_HEIGHT - 1;
	gen->draw_enemy->color = 0;
	gen->draw_enemy->tex_y = 0;
	gen->draw_enemy->d = 0;
	gen->draw_enemy->sprite_width = gen->draw_enemy->sprite_height;
	gen->draw_enemy->draw_start_x = -gen->draw_enemy->sprite_width / 2
		+ gen->draw_enemy->sprite_screen_x;
	gen->draw_enemy->draw_end_x = gen->draw_enemy->sprite_width / 2
		+ gen->draw_enemy->sprite_screen_x;
	if (gen->draw_enemy->draw_start_x < 0)
		gen->draw_enemy->draw_start_x = 0;
	if (gen->draw_enemy->draw_end_x >= WIN_WIDTH)
		gen->draw_enemy->draw_end_x = WIN_WIDTH - 1;
}

int	goated_checker(t_draw_enemy *d, t_texture *t)
{
	if (!t || !t->data || t->width <= 0 || t->height <= 0)
		return (1);
	if (d->tex_x < 0)
		d->tex_x = 0;
	else if (d->tex_x >= t->width)
		d->tex_x = t->width - 1;
	if (d->tex_y < 0)
		d->tex_y = 0;
	else if (d->tex_y >= t->height)
		d->tex_y = t->height - 1;
	return (0);
}

void	render_enemy_stripe(t_gen *g, t_texture *t, int stripe)
{
	int	y;

	g->draw_enemy->tex_x = (int)((stripe - g->draw_enemy->draw_start_x)
			* t->width / (g->draw_enemy->draw_end_x
				- g->draw_enemy->draw_start_x));
	y = g->draw_enemy->draw_start_y;
	while (y < g->draw_enemy->draw_end_y)
	{
		g->draw_enemy->d = y * 256 - WIN_HEIGHT * 128
			+ g->draw_enemy->sprite_height * 128;
		g->draw_enemy->tex_y = ((g->draw_enemy->d * t->height)
				/ g->draw_enemy->sprite_height) / 256;
		if (goated_checker(g->draw_enemy, t))
			return ;
		g->draw_enemy->color = t->data[g->draw_enemy->tex_y * t->width
			+ g->draw_enemy->tex_x];
		if ((g->draw_enemy->color & 0x00FFFFFF) != 0)
		{
			if (g->flags->terror_mode)
				g->draw_enemy->color = apply_fog(g->draw_enemy->color,
						g->draw_enemy->distance);
			copied_mlx_pixel_put(g->img_data, stripe, y, g->draw_enemy->color);
		}
		y++;
	}
}

void	draw_enemy_square(t_gen *gen, int px, int py)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			copied_mlx_pixel_put(gen->img_data, px + x, py + y, 0xdb27c9);
			x++;
		}
		y++;
	}
}
