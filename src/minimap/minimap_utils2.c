/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:19:49 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_tile_one(t_gen *gen, int x, int y, int color)
{
	int	px;
	int	py;

	py = 0;
	while (py < MINIMAP_PIXELS / gen->minimap->zoom_level)
	{
		px = 0;
		while (px < MINIMAP_PIXELS / gen->minimap->zoom_level)
		{
			copied_mlx_pixel_put(gen->img_data, x * MINIMAP_PIXELS
				/ gen->minimap->zoom_level + px, y * MINIMAP_PIXELS
				/ gen->minimap->zoom_level + py, color);
			px++;
		}
		py++;
	}
}

int	get_minimap_tile_color(t_gen *gen, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= gen->parse->height || map_x < 0)
		return (MINIMAP_GROUND_CLR);
	row_len = ft_strlen(gen->parse->map[map_y]);
	if (map_x >= row_len)
		return (MINIMAP_GROUND_CLR);
	if (gen->parse->map[map_y][map_x] == '1')
		return (MINIMAP_WALL_CLR);
	else if (gen->parse->map[map_y][map_x] == 'D')
		return (DOOR_CLR);
	else
		return (MINIMAP_GROUND_CLR);
}

void	draw_minimap_area(t_gen *gen, int start_x, int start_y)
{
	int	color;
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = -1;
	while (++y < gen->minimap->zoom_level)
	{
		x = -1;
		while (++x < gen->minimap->zoom_level)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			color = get_minimap_tile_color(gen, map_x, map_y);
			draw_minimap_tile_one(gen, x, y, color);
		}
	}
}
