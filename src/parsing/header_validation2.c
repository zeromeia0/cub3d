/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:39:28 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:31:23 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture_path_invalid(t_parsing *data, char *line, int type)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13)))
		i++;
	i += 2;
	path = ft_strtrim(&line[i], " \n\t\v\f\r");
	if (!path)
		return (1);
	if (validate_texture_file(path))
	{
		free(path);
		return (1);
	}
	if (data->textures_info[type])
		free(data->textures_info[type]);
	data->textures_info[type] = path;
	return (0);
}
