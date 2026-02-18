/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils8.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:47 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:32:43 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_strncpy(char *dst, char *srce, int n)
{
	unsigned char	*dest;
	unsigned char	*src;
	int				i;

	dest = (unsigned char *)dst;
	src = (unsigned char *)srce;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}

void	free_texture(void *mlx_ptr, t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->img)
		mlx_destroy_image(mlx_ptr, tex->img);
	free(tex);
}

void	ft_free_matrix_partial(char **matrix, int max_index)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (i < max_index)
	{
		if (matrix && matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
