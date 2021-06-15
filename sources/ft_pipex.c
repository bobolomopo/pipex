/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:19:44 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 16:30:28 by jandre           ###   ########.fr       */
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
		write(2, "pipex: no such file or directory: ", 34);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		exit(0);
	}
	dup2(infile, 0);
	close(infile);
	command = ft_split(argv[2], ' ');
	if (execve(get_command(command, envp), command, envp) == -1)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, command[0], ft_strlen(command[0]));
		write(2, "\n", 1);
		exit(0);
	}
	return (0);
}

int main_process(int *pfd, char **argv, char **envp)
{
	int		outfile;
	char	**command;

	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	close(pfd[1]);
	dup2(pfd[0], 0);
	close(pfd[0]);
	dup2(outfile, 1);
	close(outfile);
	command = ft_split(argv[3], ' ');
	if (execve(get_command(command, envp), command, envp) == -1)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, command[0], ft_strlen(command[0]));
		write(2, "\n", 1);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int 	pid;
	int		pfd[2];

	if (argc != 5)
		return (0);
	if (pipe(pfd) == -1)
	{
		write(2, "pipex: pipe failed\n", 19);
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		close(pfd[0]);
		close(pfd[1]);
		write(2, "pipex: fork failed\n", 19);
		return (0);
	}
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