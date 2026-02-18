/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   songs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:32:50 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 22:30:36 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exec_sound(t_gen *gen, const char *filename)
{
	char	*args[3];
	char	*path;

	path = "/usr/bin/paplay";
	args[0] = "paplay";
	args[1] = (char *)filename;
	args[2] = NULL;
	execve(path, args, gen->def_values->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	play_sound(t_gen *gen, const char *filename)
{
	t_sound	*sounds;
	pid_t	pid;

	sounds = &gen->def_values->sounds;
	if (sounds->count >= sounds->capacity)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (sounds->terror_music_pid > 0)
			setpgid(0, sounds->terror_music_pid);
		exec_sound(gen, filename);
	}
	else if (pid > 0)
		sounds->pids[sounds->count++] = pid;
}

const char	*random_effect(void)
{
	int			n;
	const char	*effects[] = {
		"./audio/Come Out and Play With Me.ogg",
		"./audio/Creepy Little Girl Whispering Horror Sounds (HD) (FREE).ogg",
		"./audio/The Last Of Us - Clicker Sound Effect.ogg",
	};

	n = sizeof(effects) / sizeof(effects[0]);
	return (effects[rand() % n]);
}

void	start_terror_music(t_gen *gen)
{
	t_sound	*sounds;
	pid_t	effects_pid;

	sounds = &gen->def_values->sounds;
	if (sounds->background_music_pid > 0)
		return ;
	stop_all_sounds(gen);
	play_looped_background(gen, "./audio/Background.ogg", 1);
	effects_pid = fork();
	if (effects_pid == 0)
	{
		if (sounds->background_music_pid > 0)
			setpgid(0, sounds->background_music_pid);
		srand(time(NULL) ^ getpid());
		while (1)
		{
			sleep(rand() % 15 + 10);
			play_sound(gen, random_effect());
		}
		exit(0);
	}
}

void	stop_all_sounds(t_gen *gen)
{
	t_sound		*sounds;
	pid_t		pk;
	const char	*args[] = {"pkill", "-u", getenv("USER"), "-x", "paplay", NULL};
	int			i;

	sounds = &gen->def_values->sounds;
	stop_background_and_terror(sounds);
	i = 0;
	while (i < sounds->count)
	{
		if (sounds->pids[i] > 0)
			kill(sounds->pids[i], SIGKILL);
		i++;
	}
	sounds->count = 0;
	pk = fork();
	if (pk == 0)
	{
		execvp("pkill", (char *const *)args);
		exit(1);
	}
	if (pk > 0)
		waitpid(pk, NULL, 0);
}
