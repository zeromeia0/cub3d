/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:11:59 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/17 18:11:25 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	identify_header(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
		return (E_NO);
	if (!ft_strncmp(&line[i], "SO ", 3))
		return (E_SO);
	if (!ft_strncmp(&line[i], "WE ", 3))
		return (E_WE);
	if (!ft_strncmp(&line[i], "EA ", 3))
		return (E_EA);
	if (!ft_strncmp(&line[i], "F ", 2))
		return (E_F);
	if (!ft_strncmp(&line[i], "C ", 2))
		return (E_C);
	return (-1);
}

void	write_free(char *path)
{
	write(2, "Error\nInvalid texture: ", 24);
	write(2, path, ft_strlen(path));
	free(path);
}

int	validate_texture_file(char *path)
{
	int	fd;
	int	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		if (errno == ENOENT)
			write(2, "Error\nFile texure does not exist\n", 34);
		else if (errno == EACCES)
			write(2, "Error\nNo reading permissions\n", 29);
		return (1);
	}
	close(fd);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm", 4))
	{
		write(2, "Error\nFile doesn't have right extension\n", 41);
		return (1);
	}
	return (0);
}

int	is_header_line_with_validation(t_parsing *data, char *line)
{
	int	type;

	type = identify_header(line);
	if ((type == E_NO || type == E_SO || type == E_WE || type == E_EA)
		&& is_texture_path_invalid(data, line, type))
		return (-1);
	if (type == E_F && is_rgb_colours_invalid(data, line, 'F', type))
		return (-1);
	if (type == E_C && is_rgb_colours_invalid(data, line, 'C', type))
		return (-1);
	if (type == -1)
		return (0);
	if (data->elements[type] == 1)
		return (write(2, "Error\nDouble definition of element\n", 36), -1);
	data->elements[type] = 1;
	return (1);
}

int	check_all_elements(t_parsing *data, char *line)
{
	int	i;

	i = 0;
	while (i < E_COUNT)
	{
		if (data->elements[i] == 0)
		{
			write(2, "Error\n", 6);
			write(2, "Invalid map, not all elements were defined\n", 44);
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}
