/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <Ajuln@hotmail.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:19:44 by jandre            #+#    #+#             */
/*   Updated: 2021/06/10 15:19:44 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exit_msg(int msg)
{
	if (msg == WRONG_ARG)
		write(1, "ERROR : type correct arguments like :\n\
./pipex \"infile\" ``cmd1\'\' ``cmd2\'\' \"outfile\"", 82);
	if (msg == PIPE_FAILED)
		write(1, "Pipe failed\n", 12);
	exit(0);
}

int	write_msg(char *str)
{
	write(1, "bash: ", 6);
	write(1, str, ft_strlen(str));
	write(1, ": No such file or directory\n", 28);
	return (0);
}

void opening_files(int argc, char **argv, t_pipex *pipex)
{
	pipex->fd_in_file = open(argv[1], O_RDONLY);
	pipex->fd_out_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	if (pipex->fd_in_file == -1)
		write_msg(argv[1]);
	return ;
}

int listing_commands(char **argv, t_pipex *pipex)
{
	int i;

	i = -1;
	pipex->commands = malloc(sizeof(char **) * 3);
	if (!pipex->commands)
		return (-1);
	pipex->commands[2] = NULL;
	pipex->commands[0] = ft_split(argv[1], ' ');
	if (!pipex->commands[0])
		return (-1);
	while (++i < 3)
		printf("command[0][%d] : %s\n", i, pipex->commands[0][i]);
	pipex->commands[1] = ft_split(argv[2], ' ');
	if (!pipex->commands[1])
		return (-1);
	i = -1;
	while (++i < 3)
		printf("command[0][%d] : %s\n", i, pipex->commands[1][i]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int		fd[2];

	if (argc != 5)
		return (exit_msg(WRONG_ARG));
	opening_files(argc, argv, &pipex);
	get_path(&pipex, envp);
	listing_commands(argv, &pipex);
	if (pipe(fd) < 0)
		return (exit_msg(PIPE_FAILED));
	close(pipex.fd_out_file);
	close(pipex.fd_in_file);
	return (0);
}