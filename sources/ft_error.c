/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:40:00 by jandre            #+#    #+#             */
/*   Updated: 2021/06/15 17:37:45 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipe_error(void)
{
	write(2, "pipex: pipe failed\n", 19);
	return (1);
}

int	fork_error(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
	write(2, "pipex: fork failed\n", 19);
	return (2);
}

int	command_error(char **command)
{
	if (errno == EACCES)
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, command[0], ft_strlen(command[0]));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "pipex: command not found: ", 26);
		write(2, command[0], ft_strlen(command[0]));
		write(2, "\n", 1);
	}
	return (3);
}

int	error_infile(char **argv)
{
	if (errno == EACCES)
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	else
	{
		write(2, "pipex: no such file or directory: ", 34);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
	}
	return (4);
}

int	error_outfile(char **argv)
{
	if (errno == EACCES)
	{
		write(2, "pipex: permission denied: ", 26);
		write(2, argv[4], ft_strlen(argv[4]));
		write(2, "\n", 1);
	}
	return (5);
}
