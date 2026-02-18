/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vignette_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:37:48 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_vignette_to_image(t_gen *gen, t_img_data *img)
{
	int	x;
	int	y;

	if (!gen->flags->terror_mode)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			apply_vignette_pixel(img, x, y);
			x++;
		}
		y++;
	}
}

static double	get_normalized_dist(int x, int y, t_img_data *img)
{
	double	dx;
	double	dy;
	double	max_dist;

	dx = x - (img->width / 2.0);
	dy = y - (img->height / 2.0);
	max_dist = sqrt(pow(img->width / 2.0, 2) + pow(img->height / 2.0, 2));
	return (sqrt(dx * dx + dy * dy) / max_dist);
}

static float	get_vignette_factor(double t, double inner_radius,
		double max_light)
{
	double	factor;

	if (t < inner_radius)
		factor = 1.0;
	else
	{
		factor = 1.0 - (t - inner_radius) / (1.0 - inner_radius);
		factor = pow(factor, 2.0);
	}
	factor *= max_light;
	if (factor < 0.0)
		factor = 0.0;
	return ((float)factor);
}

static void	process_vignette_row(t_img_data *img, int y, double inner,
		double max_l)
{
	int		x;
	double	t;
	float	factor;

	x = 0;
	while (x < img->width)
	{
		t = get_normalized_dist(x, y, img);
		factor = get_vignette_factor(t, inner, max_l);
		img->vignette[y * img->width + x] = factor;
		x++;
	}
}

void	init_vignette(t_img_data *img)
{
	int		y;
	double	inner;
	double	max_l;

	inner = 0.35;
	max_l = 0.6;
	img->vignette = malloc(sizeof(float) * img->width * img->height);
	if (!img->vignette)
		return ;
	y = 0;
	while (y < img->height)
	{
		process_vignette_row(img, y, inner, max_l);
		y++;
	}
}
