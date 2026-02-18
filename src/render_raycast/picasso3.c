/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:45:40 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	apply_fog(int color, double dist)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	if (dist <= FOG_START)
		return (color);
	if (dist >= FOG_END)
		return (0x000000);
	factor = 1.0 - (dist - FOG_START) / (FOG_END - FOG_START);
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

void	copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img_data->width || y < 0 || y >= img_data->height)
		return ;
	dest = img_data->addr + (y * img_data->line_len + x * (img_data->bits_pixel
				/ 8));
	*(unsigned int *)dest = color;
}
