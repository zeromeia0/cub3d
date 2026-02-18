/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:38:58 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_parsing	*parsing_init(void)
{
	t_parsing	*new;

	new = malloc(sizeof(t_parsing));
	if (!new)
		return (NULL);
	*new = (t_parsing){.textures_info = NULL, .player = '\0', .map = NULL,
		.width = 0, .height = 0, .fd = 0, .elements = {0, 0, 0, 0, 0, 0}};
	return (new);
}

void	copy_matrix(char **original_matrix, char ***matrix_to_copy_ptr)
{
	int	matrix_count;
	int	i;

	matrix_count = 0;
	while (original_matrix[matrix_count])
		matrix_count++;
	*matrix_to_copy_ptr = malloc(sizeof(char *) * (matrix_count + 1));
	if (!*matrix_to_copy_ptr)
		return ;
	i = 0;
	while (i < matrix_count)
	{
		(*matrix_to_copy_ptr)[i] = ft_strdup(original_matrix[i]);
		if (!(*matrix_to_copy_ptr)[i])
			return ;
		i++;
	}
	(*matrix_to_copy_ptr)[matrix_count] = NULL;
}

int	main_init(t_gen *gen, char *argv, char **environ)
{
	(void)argv;
	if (init_all(gen))
		return (0);
	copy_matrix(environ, &gen->def_values->env);
	return (1);
}

int	mouse_init(t_gen *gen)
{
	gen->mouse = malloc(sizeof(t_mouse));
	if (!gen->mouse)
		return (0);
	gen->mouse->x = 0;
	gen->mouse->y = 0;
	gen->mouse->previous_x = 0;
	gen->mouse->sens = MOUSE_SENS;
	return (1);
}

int	avg_img_init(t_gen *gen)
{
	gen->img_data = malloc(sizeof(t_img_data));
	if (!gen->img_data)
		return (0);
	gen->img_data->addr = NULL;
	gen->img_data->img = NULL;
	gen->img_data->endian = 0;
	gen->img_data->line_len = 0;
	gen->img_data->bits_pixel = 0;
	gen->img_data->vignette = 0;
	return (1);
}
