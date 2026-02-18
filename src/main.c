/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:16:24 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_gen	*gen_stuff(void)
{
	static t_gen	general;

	return (&general);
}

int	main(int argc, char *argv[], char **environ)
{
	t_gen	*gen;

	gen = gen_stuff();
	if (parser(gen, argc, argv))
		return (1);
	main_init(gen, argv[1], environ);
	start_window(gen, argv[1]);
	return (0);
}
