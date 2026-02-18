/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:51:04 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arm_object(t_gen *gen, t_img_data *arm)
{
	if (!arm)
		return ;
	if (arm->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, arm->img);
	free(arm);
}
