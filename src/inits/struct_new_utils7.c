/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 22:03:10 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/17 18:32:03 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*load_xpm_texture(void *mlx_ptr, char *file)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx_ptr, file, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->data = (int *)mlx_get_data_addr(tex->img, &(int){0}, &(int){0},
			&(int){0});
	return (tex);
}

int	png_name_to_xpm(t_gen *gen, char *xpm_files[4])
{
	char	*name;
	char	*dot;
	int		len;
	int		i;

	i = 0;
	while (i < 4)
	{
		name = gen->parse->textures_info[i];
		if (!name)
			return (0);
		dot = strrchr(name, '.');
		if (dot)
			len = (int)(dot - name);
		else
			len = (int)strlen(name);
		xpm_files[i] = malloc(len + ft_strlen(".xpm") + 1);
		if (!xpm_files[i])
			return (0);
		ft_strncpy(xpm_files[i], name, len);
		xpm_files[i][len] = '\0';
		ft_strcat(xpm_files[i], ".xpm");
		i++;
	}
	return (1);
}

int	png_size_fd(const char *path, uint32_t *w, uint32_t *h)
{
	int				fd;
	ssize_t			n;
	unsigned char	buf[24];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	n = read(fd, buf, sizeof(buf));
	close(fd);
	if (n != sizeof(buf))
		return (0);
	*w = (buf[16] << 24) | (buf[17] << 16) | (buf[18] << 8) | buf[19];
	*h = (buf[20] << 24) | (buf[21] << 16) | (buf[22] << 8) | buf[23];
	return (1);
}

int	color_switch(char *str)
{
	char	**all_colors;
	int		red;
	int		green;
	int		blue;
	int		final;

	all_colors = ft_split(str, ',');
	red = ft_atoi(all_colors[0]);
	green = ft_atoi(all_colors[1]);
	blue = ft_atoi(all_colors[2]);
	ft_free_matrix(all_colors);
	final = rgb_to_hex(red, green, blue);
	return (final);
}
