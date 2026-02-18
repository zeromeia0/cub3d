/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vignette_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:55:04 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:28:07 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_vignette_pixel(t_img_data *img, int x, int y)
{
	int		color;
	float	f;
	int		r;
	int		g;
	int		b;

	color = get_pixel_color_img(img, x, y);
	f = img->vignette[y * img->width + x];
	r = ((color >> 16) & 0xFF) * f;
	g = ((color >> 8) & 0xFF) * f;
	b = (color & 0xFF) * f;
	copied_mlx_pixel_put(img, x, y, (r << 16) | (g << 8) | b);
}
