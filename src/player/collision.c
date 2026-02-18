/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:42 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:31:00 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_gen *gen, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= gen->parse->height)
		return (1);
	row_len = ft_strlen(gen->parse->map[map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (1);
	return (gen->parse->map[map_y][map_x] == '1'
		|| gen->parse->map[map_y][map_x] == 'D');
}

bool	is_out_of_bounds(t_gen *gen, int y, int x)
{
	if (y < 0 || y >= gen->parse->height)
		return (true);
	if (x < 0 || x >= (int)strlen(gen->parse->map[y]))
		return (true);
	return (false);
}

bool	is_blocked(t_gen *gen, int y, int x)
{
	if (gen->parse->map[y][x] == '1')
		return (true);
	if (gen->parse->map[y][x] == 'D')
		return (true);
	return (false);
}

bool	check_corner_collision(t_gen *gen, double next_y, double next_x,
		double radius)
{
	int	y;
	int	x;

	(void)radius;
	y = (int)next_y;
	x = (int)next_x;
	if (y < 0 || x < 0 || is_out_of_bounds(gen, y, x))
		return (true);
	if (is_blocked(gen, y, x))
		return (true);
	return (false);
}

bool	collision(t_gen *gen, double next_y, double next_x)
{
	double	radius;

	radius = 0.2;
	if (check_corner_collision(gen, next_y - radius, next_x - radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y - radius, next_x + radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y + radius, next_x - radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y + radius, next_x + radius, radius))
		return (true);
	return (false);
}
