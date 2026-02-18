/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:06:11 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_there_garbage(char *line)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(line, " \n");
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ' && !ft_isdigit(tmp[i]))
			return (free(tmp), 1);
		i++;
	}
	return (free(tmp), 0);
}

static int	not_one_number(char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			found++;
			while (ft_isdigit(line[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (found != 1);
}

static void	rgb_error_message(void)
{
	write(2, "Error\n", 6);
	write(2, "Invalid colour element\n", 24);
}

int	validate_rgb_values(char **all_colors)
{
	int	i;
	int	rgb;

	if (ft_matrix_len(all_colors) != 3)
		return (rgb_error_message(), 1);
	i = 0;
	while (i < 3)
	{
		if (is_there_garbage(all_colors[i]) || not_one_number(all_colors[i]))
			return (rgb_error_message(), 1);
		rgb = ft_atoi(all_colors[i]);
		if (rgb < 0 || rgb > 255)
			return (rgb_error_message(), 1);
		i++;
	}
	return (0);
}

int	is_rgb_colours_invalid(t_parsing *data, char *line, char c, int type)
{
	char	**all_colors;
	int		i;
	int		start;

	i = 0;
	while (line[i] == ' ' || line[i] == c)
		i++;
	start = i;
	if (!ft_strrchr(&line[i], ','))
		return (rgb_error_message(), 1);
	all_colors = ft_split(&line[i], ',');
	if (!all_colors)
		return (1);
	if (validate_rgb_values(all_colors))
		return (free_double(all_colors), 1);
	if (data->textures_info[type])
		free(data->textures_info[type]);
	data->textures_info[type] = ft_strdup(line + start);
	return (free_double(all_colors), 0);
}
