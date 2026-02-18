/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:42:32 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:32:06 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_gen *gen, t_texture **dst, char **xpm_files, int count)
{
	int	bpp;
	int	sl;
	int	endian;
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i]->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
				xpm_files[i], &dst[i]->width, &dst[i]->height);
		if (!dst[i]->img)
		{
			printf("Failed to load texture %d: %s\n", i, xpm_files[i]);
			exit(1);
		}
		dst[i]->data = (int *)mlx_get_data_addr(dst[i]->img, &bpp, &sl,
				&endian);
		i++;
	}
}

void	wall_textures_init(t_gen *gen)
{
	if (!init_xpm_paths(gen))
	{
		ft_putstr_fd("Failed to convert normal PNG names\n", 2);
		exit(1);
	}
	load_all_textures(gen, gen->xpm_paths);
	free_xpm_paths(gen->xpm_paths);
	free(gen->xpm_paths);
	gen->xpm_paths = NULL;
}

void	init_start(t_gen *gen)
{
	gen->dda->start_x = (int)gen->player->x;
	gen->dda->start_y = (int)gen->player->y;
	gen->dda->wall_hit = 0;
	gen->dda->side = 0;
}

void	init_delta(t_gen *gen, double ray_x, double ray_y)
{
	gen->dda->delta_x = fabs(1.0 / ray_x);
	gen->dda->delta_y = fabs(1.0 / ray_y);
}

void	init_line(int *coords, int *vars)
{
	vars[0] = ft_abs(coords[2] - coords[0]);
	vars[1] = ft_abs(coords[3] - coords[1]);
	if (coords[0] < coords[2])
		vars[2] = 1;
	else
		vars[2] = -1;
	if (coords[1] < coords[3])
		vars[3] = 1;
	else
		vars[3] = -1;
	vars[4] = vars[0] - vars[1];
}
