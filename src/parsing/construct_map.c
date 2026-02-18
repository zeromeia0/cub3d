/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:09:42 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	allocate_textures(t_parsing *data)
{
	data->textures_info = ft_calloc(E_COUNT + 1, sizeof(char *));
	if (!data->textures_info)
	{
		write(2, "Error\nAllocation failed\n", 25);
		return (1);
	}
	return (0);
}

static char	*skip_header_and_empty_lines(t_parsing *data)
{
	char	*line;
	int		header;

	line = get_next_line(data->fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(data->fd);
			continue ;
		}
		header = is_header_line_with_validation(data, line);
		if (header == 1)
		{
			free(line);
			line = get_next_line(data->fd);
			continue ;
		}
		if (header == -1)
			return (free(line), NULL);
		return (line);
	}
	write(2, "Error\nInvalid map, map not found\n", 34);
	return (NULL);
}

static char	**get_map_with_style(t_parsing *data, int count)
{
	char		**map;
	char *const	line = get_next_line(data->fd);

	map = NULL;
	if (line != NULL)
		map = get_map_with_style(data, count + 1);
	else if (count)
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
		{
			write(2, "Error\nAllocation failed\n", 25);
			return (free(line), NULL);
		}
	}
	if (map)
		map[count] = line;
	return (map);
}

static void	get_height_and_max_width(t_parsing *data)
{
	int	length;

	while (data->map[data->height])
	{
		length = ft_strlen(data->map[data->height]);
		data->width = (int []){
			data->width,
			length
		}
		[data->width < length];
		data->height++;
	}
}

int	construct_map_and_textures(t_parsing *data)
{
	char	*line;

	if (allocate_textures(data))
		return (1);
	line = skip_header_and_empty_lines(data);
	if (!line || check_all_elements(data, line))
		return (1);
	data->map = get_map_with_style(data, 1);
	if (!data->map)
		return (free(line), 1);
	data->map[0] = line;
	get_height_and_max_width(data);
	return (close(data->fd), 0);
}
