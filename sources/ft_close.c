/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jandre <jandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:01:29 by jandre            #+#    #+#             */
/*   Updated: 2021/06/11 15:05:23 by jandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_close(t_pipex *pipex)
{
	int		i;
	int		j;

	i = -1;
	close(pipex->fd_in_file);
	close(pipex->fd_out_file);
	while (pipex->path[++i] != NULL)
		free(pipex->path[i]);
	free(pipex->path);

}