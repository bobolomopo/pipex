/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:19:44 by jandre            #+#    #+#             */
/*   Updated: 2021/06/11 16:13:42 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	exit_msg(int msg)
{
	if (msg == WRONG_ARG)
		write(1, "ERROR : type correct arguments like :\n\
./pipex \"infile\" \"cmd1\" \"cmd2\" \"outfile\"\n", 79);
	if (msg == PIPE_FAILED)
		write(1, "Pipe failed\n", 12);
	exit(0);
}

int comm_not_found(char *str)
{
	write(1, "zsh: command not found: ", 24);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

int	write_msg(char *str)
{
	write(1, "zsh: No such file or directory: ", 32);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
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

int listing_commands(char **argv, t_pipex *pipex, int *fd)
{
	pipex->commands = malloc(sizeof(char **) * 3);
	if (!pipex->commands)
		return (ft_close(pipex, fd, 0));
	pipex->commands[2] = NULL;
	pipex->commands[0] = ft_split(argv[2], ' ');
	pipex->commands[1] = ft_split(argv[3], ' ');
	if (!pipex->commands[0])
		return (ft_close(pipex, fd, 0));
	if (!pipex->commands[1])
		return (ft_close(pipex, fd, 0));
	return (0);
}

int	joining_path_commands(t_pipex *pipex, int *fd)
{
	char 	*temp;
	char	*temp2;
	int		i;
	int		j;
	int		fd_temp;

	i = -1;
	while (pipex->commands[++i])
	{
		j = -1;
		while (pipex->path[++j])
		{
			temp = ft_strjoin(pipex->path[j], "/");
			temp2 = temp;
			temp = ft_strjoin(temp2, pipex->commands[i][0]);
			free(temp2);
			if (!temp)
				return (ft_close(pipex, fd, 0));
			fd_temp = open(temp, O_RDONLY);
			if (fd_temp > 0)
			{
				free(pipex->commands[i][0]);
				pipex->commands[i][0] = ft_strdup(temp);
				if (!pipex->commands[i][0])
					return (ft_close(pipex, fd, 0));
				free(temp);
				close(fd_temp);
				break ;
			}
			free(temp);
		}
		if (!pipex->path[j])
			comm_not_found(pipex->commands[i][0]);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (exit_msg(WRONG_ARG));
	opening_files(argc, argv, &pipex);
	get_path(&pipex, envp, fd);
	listing_commands(argv, &pipex, fd);
	joining_path_commands(&pipex, fd);
	if (pipe(fd) < 0)
		return (ft_close(&pipex, fd, 0));
	pid1 = fork();
	if (pid1 < 0)
		return (ft_close(&pipex, fd, 0));
	if (pid1 == 0)
	{
		close(fd[0]);
		if (pipex.fd_in_file < 0)
			ft_close(&pipex, fd, 0);
		dup2(pipex.fd_in_file, STDIN);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		if (execve(pipex.commands[0][0], pipex.commands[0], envp) == -1)
			ft_close(&pipex, fd, 0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (ft_close(&pipex, fd, 0));
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN);
		dup2(pipex.fd_out_file, STDOUT);
		if (execve(pipex.commands[1][0], pipex.commands[1], envp) == -1)
			ft_close(&pipex, fd, 0);
	}
	wait(NULL);
	wait(NULL);
	ft_close(&pipex, fd, 0);
	return (0);
}