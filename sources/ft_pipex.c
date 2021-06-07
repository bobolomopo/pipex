/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 11:58:02 by jandre            #+#    #+#             */
/*   Updated: 2021/06/07 16:30:54 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int pipex(t_pipex *pipex, char**envp)
{
	int	pids[pipex->number_process];
	int **pipes;
	int	i;
	int	j;

	// Initialisation des pipes mettre fonction a part
	//////////
	i = 0;
	pipes = malloc(sizeof(int *) * (pipex->number_process + 1));
	if (!pipex)
		return (error_malloc(pipex));
	while (i < pipex->number_process + 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (error_malloc(pipex));
	}
	while (i < pipex->number_process + 1)
	{
		if (pipe(pipes[i]) == -1)
			return (error_pipe(pipex, pipes));
		i++;
	}
	//////////
	i = 0;
	while (i < pipex->number_process)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (error_fork(pipex, pipes));
		// debut child process
		if (pids[i] == 0) // ID process zero -> child process
		{
			// Closing everypipe the current child doesnt need, can go into another fonction
			///////////////////////
			j = -1;
			while (++j < pipex->number_process + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
			}
			/// on dup tout les infile outfile pour simuler les pipes
			if (i != 0 && i != pipex->number_process)
			{
				dup2(pipes[i - 1][0], STDIN);
				dup2(pipes[i][1], STDOUT);
			}
			else if (i != pipex->number_process)
			{
				dup2(pipes[0][0], pipex->fd_in_file);
				dup2(pipes[i][1], STDOUT);
			}
			else
			{
				dup2(pipes[i - 1][0], STDIN);
				dup2(pipes[i][1], pipex->fd_out_file);
			}
			//////////////////////
			j = find_which_path(pipex, pipex->commands[i]);
			if (j >= 0)
			{
				if (execve(pipex->path[j], pipex->commands[i], envp) == -1)
					return(error_execute(pipex, pipes));
			}
			else
				return(error_execute(pipex, pipes));
			close(pipes[i - 1][0]);
			close(pipes[i][1]);
			return (EXIT_SUCCESS);
		}
	}
	i = -1;
	while (++i < pipex->number_process)
		wait(NULL); // chaque processus parent attend que son processus child termine avant de terminer
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int		i;

	pipex.number_process = argc - 3;
	pipex.commands = malloc(sizeof(char **) * (pipex.number_process + 1));
	if (!pipex.commands)
		return (error_malloc(&pipex));
	pipex.in_file = malloc(sizeof(char *) * ft_strlen(argv[1]));
	if (!pipex.in_file)
		return (error_malloc(&pipex));
	pipex.out_file = malloc(sizeof(char *) * ft_strlen(argv[argc - 1]));
	if (!pipex.out_file)
		return (error_malloc(&pipex));
	i = 0;
	while (i < pipex.number_process)
	{
		// on rempli les commandses successives
		pipex.commands[i] = ft_split(argv[i + 2], ' ');
		if (!pipex.commands[i])
			return (error_commands(&pipex));
		i++;
	}
	pipex.commands[i] = NULL;
	pipex(&pipex, envp);
	return (0);
}