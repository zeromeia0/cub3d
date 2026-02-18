/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:05:53 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_partial_copy(char **copy, int last)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < last)
	{
		free(copy[i]);
		i++;
	}
	free(copy);
}

static int	ft_floodfill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'L')
		return (0);
	map[y][x] = 'L';
	if (ft_floodfill(map, y + 1, x))
		return (1);
	if (ft_floodfill(map, y - 1, x))
		return (1);
	if (ft_floodfill(map, y, x + 1))
		return (1);
	if (ft_floodfill(map, y, x - 1))
		return (1);
	return (0);
}

char	**create_copy_map(t_parsing *data)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		return (write(2, "Error: Allocation failed\n", 26), NULL);
	i = -1;
	while (++i < data->height)
	{
		copy[i] = malloc(sizeof(char) * (data->width + 1));
		if (!copy[i])
			return (write(2, "Error: Allocation failed\n", 26),
				free_partial_copy(copy, i), NULL);
		j = 0;
		while (j < data->width)
			copy[i][j++] = ' ';
		ft_memcpy(copy[i], data->map[i], ft_strlen(data->map[i]));
		copy[i][data->width] = '\0';
	}
	copy[i] = NULL;
	return (copy);
}

int	is_map_valid(t_parsing *data)
{
	char	**copy;
	int		y;
	int		x;

	copy = create_copy_map(data);
	if (!copy)
		return (1);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (copy[y][x] == '0' || copy[y][x] == data->player)
			{
				if (ft_floodfill(copy, y, x))
				{
					write(2, "Error\n", 6);
					write(2, "Invalid map, not surrounded by walls.\n", 39);
					return (free_double(copy), 1);
				}
			}
		}
	}
	return (free_double(copy), 0);
}
