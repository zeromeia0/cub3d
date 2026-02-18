/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:30 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:30:06 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color(t_gen *gen, int x, int y)
{
	char	*pixel;
	int		color;

	if (!gen->arm || !gen->arm->addr)
		return (0);
	if (x < 0 || x >= (int)gen->texture_data->arm_width || y < 0
		|| y >= (int)gen->texture_data->arm_height)
		return (0);
	pixel = gen->arm->addr + (y * gen->arm->line_len + x * (gen->arm->bits_pixel
				/ 8));
	color = *(int *)pixel;
	return (color);
}

int	get_pixel_color_img(t_img_data *img, int x, int y)
{
	char	*pixel;

	if (!img || !img->addr)
		return (0);
	if (x < 0 || x >= img->line_len / (img->bits_pixel / 8) || y < 0)
		return (0);
	pixel = img->addr + y * img->line_len + x * (img->bits_pixel / 8);
	return (*(int *)pixel);
}

void	draw_arm(t_gen *gen)
{
	int	start_x;
	int	start_y;
	int	color;
	int	x;
	int	y;

	if (!gen || !gen->arm)
		return ;
	start_x = gen->mlx_data->win_width - gen->texture_data->arm_width;
	start_y = gen->mlx_data->win_height - gen->texture_data->arm_height;
	y = 0;
	while (y < (int)gen->texture_data->arm_height)
	{
		x = 0;
		while (x < (int)gen->texture_data->arm_width)
		{
			color = get_pixel_color(gen, x, y);
			if (color != (0xB30000 | 0x00FF00))
				copied_mlx_pixel_put(gen->img_data, start_x + x, start_y + y,
					color);
			x++;
		}
		y++;
	}
}

void	draw_terror_arm(t_gen *gen)
{
	int	start_x;
	int	start_y;
	int	color;
	int	x;
	int	y;

	if (!gen || !gen->arm)
		return ;
	start_x = gen->mlx_data->win_width - gen->texture_data->terror_arm_width;
	start_y = gen->mlx_data->win_height - gen->texture_data->terror_arm_height;
	y = 0;
	while (y < (int)gen->texture_data->terror_arm_height)
	{
		x = 0;
		while (x < (int)gen->texture_data->terror_arm_width)
		{
			color = get_pixel_color_img(gen->terror_arm, x, y);
			if (color != TERROR_ARM_TRANSPARENT)
				copied_mlx_pixel_put(gen->img_data, start_x + x, start_y + y,
					color);
			x++;
		}
		y++;
	}
}
