/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:19:44 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 17:36:37 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	child_process(int *pfd, char **argv, char **envp)
{
	int		infile;
	char	**command;

	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		error_infile(argv);
		exit(0);
	}
	dup2(infile, 0);
	close(infile);
	command = ft_split(argv[2], ' ');
	if (execve(get_command(command, envp), command, envp) == -1)
	{
		command_error(command);
		exit(0);
	}
	return (0);
}

int	main_process(int *pfd, char **argv, char **envp)
{
	int		outfile;
	char	**command;

	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 644);
	if (outfile == -1)
	{
		error_outfile(argv);
		exit(0);
	}
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	dup2(outfile, 1);
	close(outfile);
	command = ft_split(argv[3], ' ');
	if (execve(get_command(command, envp), command, envp) == -1)
	{
		command_error(command);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pid;
	int		pfd[2];

	if (argc != 5)
		return (0);
	if (pipe(pfd) == -1)
		return (pipe_error());
	pid = fork();
	if (pid == -1)
		return (fork_error(pfd));
	if (pid == 0)
		child_process(pfd, argv, envp);
	pid = fork();
	if (pid == 0)
		main_process(pfd, argv, envp);
	close(pfd[0]);
	close(pfd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
