/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:08:02 by jandre            #+#    #+#             */
/*   Updated: 2021/06/07 16:44:00 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int error_malloc(t_pipex *pipex)
{
	int		i;
	int		j;

	i = 0;
	if (pipex->commands)
	{
		while (pipex->commands[i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->in_file)
		free(pipex->in_file);
	if (pipex->out_file)
		free(pipex->out_file);
	i = -1;
	while (pipex->path[++i])
		free(pipex->commands[i]);
	perror(NULL);
	exit(0);
}

int error_pipe(t_pipex *pipex, int **pipe)
{
	int		i;
	int		j;

	i = 0;
	if (pipex->commands)
	{
		while (pipex->commands[i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->in_file)
		free(pipex->in_file);
	if (pipex->out_file)
		free(pipex->out_file);
	i = -1;
	while (pipex->path[++i])
		free(pipex->commands[i]);
	while (i < pipex->number_process)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		if (pipe[i])
			free(pipe[i]);
	}
	if (pipe)
		free(pipe);
	perror(NULL);
	exit(0);
}

int	error_execute(t_pipex *pipex, int **pipe)
{
	int		i;
	int		j;

	i = 0;
	if (pipex->commands)
	{
		while (pipex->commands[i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->in_file)
		free(pipex->in_file);
	if (pipex->out_file)
		free(pipex->out_file);
	i = -1;
	while (pipex->path[++i])
		free(pipex->commands[i]);
	i = 0;
	while (i < pipex->number_process)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		if (pipe[i])
			free(pipe[i]);
	}
	if (pipe)
		free(pipe);
	perror(NULL);
	exit(0);

}

int	error_fork(t_pipex *pipex, int **pipe)
{
	int		i;
	int		j;

	i = 0;
	if (pipex->commands)
	{
		while (pipex->commands[i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->in_file)
		free(pipex->in_file);
	if (pipex->out_file)
		free(pipex->out_file);
	i = -1;
	while (pipex->path[++i])
		free(pipex->commands[i]);
	while (i < pipex->number_process)
	{
		close(pipe[i][0]);
		close(pipe[i][1]);
		if (pipe[i])
			free(pipe[i]);
	}
	if (pipe)
		free(pipe);
	perror(NULL);
	exit(0);
}

int	error_commands(t_pipex *pipex)
{
	int		i;
	int		j;

	i = 0;
	if (pipex->commands)
	{
		while (pipex->commands[i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
			i++;
		}
		free(pipex->commands);
	}
	if (pipex->in_file)
		free(pipex->in_file);
	if (pipex->out_file)
		free(pipex->out_file);
	i = -1;
	while (pipex->path[++i])
		free(pipex->commands[i]);
	perror(NULL);
	exit(0);
}