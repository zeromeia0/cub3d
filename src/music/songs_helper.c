/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   songs_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:16:25 by vivaz-ca          #+#    #+#             */
/*   Updated: 2026/02/17 18:31:33 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stop_background_music(t_sound *sounds)
{
	if (sounds->background_music_pid > 0)
	{
		kill(sounds->background_music_pid, SIGKILL);
		sounds->background_music_pid = 0;
	}
}

void	background_supervisor(t_gen *gen, const char *filename,
		int is_terror)
{
	pid_t	play_pid;

	if (is_terror)
		setpgid(0, 0);
	while (1)
	{
		play_pid = fork();
		if (play_pid == 0)
		{
			if (is_terror)
				setpgid(0, getpgid(getpid()));
			exec_sound(gen, filename);
			perror("execve background");
			exit(1);
		}
		else if (play_pid > 0)
			waitpid(play_pid, NULL, 0);
		else
		{
			perror("fork play");
			break ;
		}
	}
	exit(0);
}

void	play_looped_background(t_gen *gen, const char *filename, int is_terror)
{
	t_sound	*sounds;
	pid_t	supervisor_pid;

	sounds = &gen->def_values->sounds;
	stop_background_music(sounds);
	supervisor_pid = fork();
	if (supervisor_pid < 0)
	{
		perror("fork background");
		return ;
	}
	if (supervisor_pid == 0)
		background_supervisor(gen, filename, is_terror);
	else
	{
		sounds->background_music_pid = supervisor_pid;
		if (is_terror)
		{
			sounds->terror_music_pid = supervisor_pid;
			setpgid(supervisor_pid, supervisor_pid);
		}
	}
}

void	stop_background_and_terror(t_sound *sounds)
{
	if (sounds->background_music_pid > 0)
	{
		kill(sounds->background_music_pid, SIGTERM);
		usleep(100000);
		kill(sounds->background_music_pid, SIGKILL);
		sounds->background_music_pid = 0;
	}
	if (sounds->terror_music_pid > 0
		&& sounds->terror_music_pid != sounds->background_music_pid)
	{
		kill(-sounds->terror_music_pid, SIGKILL);
		sounds->terror_music_pid = 0;
	}
}

void	handle_audio_keys(int key, t_gen *gen)
{
	const char	*audio_files[5] = {"./audio/default1.ogg",
		"./audio/default2.ogg", "./audio/default3.ogg",
		"./audio/default4.ogg", "./audio/default5.ogg"};
	int			index;

	if ((key >= XK_1 && key <= XK_5) && !gen->flags->terror_mode)
	{
		index = key - XK_1;
		gen->flags->music_on = !gen->flags->music_on;
		stop_all_sounds(gen);
		play_sound(gen, audio_files[index]);
		if (key == XK_1)
			gen->kboard->key_num_one = true;
		if (key == XK_2)
			gen->kboard->key_num_two = true;
		if (key == XK_3)
			gen->kboard->key_num_three = true;
		if (key == XK_4)
			gen->kboard->key_num_four = true;
		if (key == XK_5)
			gen->kboard->key_num_five = true;
	}
	if (key == XK_6 && !gen->flags->terror_mode)
		stop_all_sounds(gen);
}
