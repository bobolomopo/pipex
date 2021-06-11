/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:01:29 by jandre            #+#    #+#             */
/*   Updated: 2021/06/11 15:42:47 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_close(t_pipex *pipex, int *fd, int status)
{
	int		i;
//	int		j;

	i = -1;
	close(fd[0]);
	close(fd[1]);
	close(pipex->fd_in_file);
	close(pipex->fd_out_file);
	/*while (pipex->path[++i] != NULL)
		free(pipex->path[i]);
	if(pipex->path)
		free(pipex->path);
	i = -1;
	if (pipex->commands)
	{
		while (pipex->commands[++i])
		{
			j = -1;
			while (pipex->commands[i][++j])
				free(pipex->commands[i][j]);
			free(pipex->commands[i]);
		}
		free(pipex->commands);
	}*/
	if (status == 0)
		exit(0);
	return (0);
}